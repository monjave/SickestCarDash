// VehicleParser.cpp
#include "VehicleParser.h"

/**
 * @brief Construct a new Vehicle Parser:: Vehicle Parser object
 * @note pidTable values come from [Wikipedia](https://en.wikipedia.org/wiki/OBD-II_PIDs#Service_03)
 */
VehicleParser::VehicleParser() { loadPidTable(); };

/**
 * @brief Construct a new Replay Parser< T>:: Replay Parser object. Importantly,
 * you must provide it with the location of the immediate parent directory of
 * the telemetry files. This may take time to compile depending on the size of
 * the files being loaded.
 *
 * @param filePath
 */
VehicleParser::VehicleParser(std::string filePath, QObject* parent) {
    loadPidTable();
    std::filesystem::path directoryPath = filePath;    

    if (!std::filesystem::exists(directoryPath)) {
      throw std::invalid_argument("Directory does not exist: " + filePath);
    }
  
    loadSave(directoryPath);
    _location26 = 0;
    _location78 = 0;
    _location20 = 0;
}

/**
 * @brief slot that sends data to the `PublishToMiddleware()` method
 *
 * @note This is only useful for MVP, will need to be rewritten after implementation of a `saveTelemetry()` method
 */
void VehicleParser::dataRegulator() {
  QTimer* timer = qobject_cast<QTimer*>(sender());
  bool shouldContinue = (
    _location20 < _replayData["time"].size() && 
    _location26 < _replayData["speed"].size() && 
    _location78 < _replayData["gear"].size()
  );
  
  if (shouldContinue) {
    double data;
    std::string pidTableKey;
    int8_t success;
    if (timer == nullptr) {
      qDebug("Signal from QTimer not found");
      return;
    } else if (timer == timer26) { // push speed, rpm, and throttle to middleware
      qDebug() << "Tick 26!";
      qDebug() << "speed: " << getValue("speed", _location26);
      qDebug() << "rpms: " << getValue("rpms", _location26);
      qDebug() << "throttle: " << getValue("throttle", _location26);

      data = _replayData["speed"][_location26];
      emit dataReady(0, data);
      pidTableKey = "SPEED";
      success = PublishToMiddleware(_buffMan, data, pidTableKey);

      data = _replayData["rpms"][_location26];
      emit dataReady(1, data);
      pidTableKey = "RPM";
      success = PublishToMiddleware(_buffMan, data, pidTableKey);

      data = _replayData["throttle"][_location26];
      pidTableKey = "THROTTLE";
      success = PublishToMiddleware(_buffMan, data, pidTableKey);

      _location26++;
    } else if (timer == timer78) { // push gear to middlewear
      qDebug() << "Tick 78!";
      qDebug() << "gear: " << getValue("gear", _location78);
      data = _replayData["gear"][_location78];
      emit dataReady(6, data);
      pidTableKey = "GEAR";
      success = PublishToMiddleware(_buffMan, data, pidTableKey);
      
      _location78++;
    } else if (timer == timer20) { // reduce time to know when to stop timers
      qDebug() << "Tick 20!";
      qDebug() << "time: " << getValue("time", _location20);
      emit dataReady(4, getValue("time", _location20));

      _location20++;
    }
  } else {
    timer26->stop();
    timer78->stop();
    timer20->stop();
  }
}

/**
 * @brief starts the timers.
 * 
 */
void VehicleParser::replayStart(){
  this->timer26 = new QTimer(this);
  connect(timer26, &QTimer::timeout, this, &VehicleParser::dataRegulator);
  timer26->start(26);

  this->timer78 = new QTimer(this);
  connect(timer78, &QTimer::timeout, this, &VehicleParser::dataRegulator);
  timer78->start(78);

  this->timer20 = new QTimer(this);
  connect(timer20, &QTimer::timeout, this, &VehicleParser::dataRegulator);
  timer20->start(20);
}

/**
 * @brief 
 * @param request The request to be made to the OBD-II Interface
 */
void VehicleParser::Request(VehicleConnection* connection, const std::string& request) {
  std::string code = _pidTable[request].first;
  QString obdCode = QString::fromStdString(code);
  
  connection->sendCommand(obdCode);
}


// TODO - Need to be able to take in a QString, not just a regular string

/// @brief Extracts the last two bytes of the response data from the vehicle
/// @param hexString
/// @return Returns a std::pair<bool, int> representing if the conversion is successful and what the value is.
std::pair<bool, int> VehicleParser::ExtractData(const std::string& hexString) {
  try {
    size_t processed = 0;
    int value = std::stoi(hexString, &processed, 16);

    if (processed != hexString.size()) {
      return {false, INT_MIN};
    }

    value &= 0xFF;

    return {true, value};
  } catch (const std::exception& e) {
    std::cerr << "Hex conversion error: " << e.what() << '\n';
    return {false, INT_MIN};
  }
}

/// @brief An overload for ExtractData() that takes in a QString instead of a C string
/// @param hexString The hex string to be converted to an int
/// @return Returns a std::pair<bool, int> representing if the conversion is successful and what the value is.
std::pair<bool, int> VehicleParser::ExtractData(const QString& hexString) {
  return ExtractData(hexString.toStdString());
}

/// @brief Initializes the OBD-II connection by creating a new VehicleConnection object 
/// @returns Returns a pointer to the newly created VehicleConnection object
VehicleConnection* VehicleParser::initOBDConnection() {
  VehicleConnection* connection = new VehicleConnection();

  return connection;
}

// @brief Publish to the middleware what an OBD query has returned.
// @param data
// @return Return 0 if successful, return a 1 if there's an issue.
// Need to validate if BuffMan is a valid CircularBufferManager object, but how?
// int8_t VehicleParser::PublishToMiddleware(CircularBufferManager& BuffMan,
//                                           int& data,
//                                           std::string& pidTableKey) 
//   {
//   if (_pidTable.find(pidTableKey) == _pidTable.end()) {
//     std::cout << "Key provided has no value in _pidTable.\n";
//     return 1;
//   }

//   return BuffMan.publish(data, _pidTable[pidTableKey].second);
// }

/// @brief Publish to the middleware what an OBD query has returned.
/// @param data
/// @return Return 0 if successful, return a 1 if there's an issue.
int8_t VehicleParser::PublishToMiddleware(CircularBufferManager& BuffMan,
                                          double& data,
                                          std::string& pidTableKey) 
  {
  if (_pidTable.find(pidTableKey) == _pidTable.end()) {
    std::cout << "Key provided has no value in _pidTable.\n";
    return 1;
  }
  BuffMan.publish(data, _pidTable[pidTableKey].second);
  emit BuffMan.dataReady();
  return 0;
}

std::pair<std::string, int> VehicleParser::getPIDTable(const std::string& key) {
  if (_pidTable.find(key) == _pidTable.end()) 
  {
    std::cout << "Key provided to getPIDTAble() is invalid.";
    return {};
  }

  return _pidTable[key];
}

/**
 * @brief stages all the data files from their parent directory and calls them
 * to be loaded one-by-one.
 *
 * @note this function takes in the path to a directory, not a file
 * @param directory path
 */
void VehicleParser::loadSave(std::filesystem::path directoryPath) {
  for (const auto& path_fileName :
       std::filesystem::directory_iterator(directoryPath)) {
    std::filesystem::path filePath = path_fileName.path();
    std::fstream file(filePath.string());
    readCSV(file);
    file.close();
  }
}

/**
 * @brief reads a CSV file and loads the information into the _replayData
 * structure. Requires the CSV file to be of the format:
 *
 * ```
 * header, header, header, ...
 * data, data, data, ...
 * data, data, data, ...
 * ...
 * ```
 * @param file
 */
void VehicleParser::readCSV(std::fstream& file) {
  if (file.is_open()) {
    std::vector<std::string> headers;
    std::string line;
    std::string header;
    std::getline(file, line);
    std::stringstream stream(line);

    // retrieve headers from the file
    while (std::getline(stream, header, ',')) {
      headers.push_back(header);
      _replayData[header] = {};
    }

    // retrieve data from the file
    while (std::getline(file, line)) {
      std::stringstream secondStream(line);
      std::string num;
      double double_value;
      int column = 0;

      while (std::getline(secondStream, num, ',')) {
        try {
          double_value = std::stod(num);
        } catch (const std::invalid_argument& e) {
          throw std::invalid_argument("Invalid Argument: Unable to convert '" +
                                      num + "' to double.");
        } catch (const std::out_of_range& e) {
          throw std::invalid_argument(
              "Out of Range: Value '" + num +
              "' is too large or too small to convert to double.");
        }
        _replayData[headers[column]].push_back(double_value);
        column++;
      }
    }
  } else {
    file.close();
    throw std::invalid_argument("file could not be opened");
  }
  _replayData.erase("");
  file.close();
}

/// @brief Get the stored replay data from the Vehicleparser object
/// @return Returns a map holding the data.
std::map<std::string, std::vector<double>>& VehicleParser::getData() {
  return _replayData;
}

/**
 * @note Depricated method
 * @brief removes the first value of the vector associated with a provided key. Not currently used anymore to preserve data structure integrity.
 *
 * @param key
 */
void VehicleParser::removeReplayDataFromFront(std::string key) {
  _replayData[key].erase(_replayData[key].begin());
}

/**
 * @brief Prints all of the available pid table names and the number of
 * values in their corresponding vectors. If the desiredFileLocation is not
 * already a CSV file, this program will create it.
 *
 * @param desiredFileLocation
 */
void VehicleParser::printValueToFile(std::string desiredFileLocation) {
  std::string outputFilePath = desiredFileLocation;

  std::ofstream file(outputFilePath);
  if (!file.is_open()) {
    std::cerr << "Failed to create or open file: " << outputFilePath
              << std::endl;
    return;
  }

  for (const auto& column : _replayData) {
    file << std::left << std::setw(10) << "Column:" << std::setw(20)
         << column.first << "Rows: " << std::setw(10) << column.second.size()
         << "Values: " << std::endl;
  }
  file.close();
}

/**
 * @brief returns the value in the key at a given index in the indicated vector in the _replayData map
 * 
 * @param key 
 * @param index 
 * @return double 
 */
double VehicleParser::getValue(std::string key, int index){
  double returnValue = _replayData[key][index];
  return returnValue;
}

CircularBufferManager* VehicleParser::getBufferManager(){
  return &_buffMan;
}

/**
 * @brief loads all the relevant values into the `_pidTable` class variable
 */
void VehicleParser::loadPidTable() {
  _pidTable = {
      // **** NOT IN BUFFER ****
      {"RESET", {"ATZ", -1}},
      {"ECHOOFF", {"ATE0", -1}},
      {"NOLINEFEED", {"ATL0", -1}},
      {"NOSPACES", {"ATS0", -1}},
      {"AUTOPRTCL", {"ATSP0", -1}},
      // ***********************
      {"SPEED", {"010D", 0}},      // Buffer 0
      {"RPM", {"010C", 1}},        // Buffer 1
      {"FUEL", {"012F", 2}},       // Buffer 2
      {"WATERTEMP", {"0105", 3}},  // Buffer 3
      {"THROTTLE", {"0111", 4}},   // Buffer 4
      {"OILTEMP", {"015C", 5}},    // Buffer 5
      {"GEAR", {"01A4", 6}},       // Buffer 6
      {"BATTVOLTS", {"0142", 7}},  // Buffer 7
      {"STOREDDTC", {"03", 8}}     // Buffer 8
  };
}
