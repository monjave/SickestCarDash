// VehicleParser.cpp
#include "VehicleParser.h"

// pidTable values come from
// https://en.wikipedia.org/wiki/OBD-II_PIDs#Service_03
VehicleParser::VehicleParser() { loadPidTable(); };

/**
 * @brief Construct a new Replay Parser< T>:: Replay Parser object. Importantly,
 * you must provide it with the location of the immediate parent directory of
 * the telemetry files. This may take time to compile depending on the size of
 * the files being loaded.
 *
 * @tparam T
 * @param filePath
 */
VehicleParser::VehicleParser(std::string filePath, QObject* parent) {
  loadPidTable();
  std::filesystem::path directoryPath = filePath;

  std::cout << "DEBUG DIRECTORYPATH: " << filePath << "\n";
  

  if (!std::filesystem::exists(directoryPath)) {
    throw std::invalid_argument("File does not exist: " + filePath);
  }

  if (!std::filesystem::is_regular_file(directoryPath)) {
      throw std::invalid_argument("Expected a regular file: " + filePath);
  }
 
  loadSave(directoryPath);
}

/**
 * @brief slot that sends data to the `PublishToMiddleware()` method
 * ! This is quick and dirty, fix this later
 * ! Add a early stop function
 *
 */
void VehicleParser::dataRegulator() {
  qDebug() << "Tick!";  // for when we migrate to QTest
  QTimer* timer = qobject_cast<QTimer*>(sender());
  CircularBufferManager buffMan = CircularBufferManager<int>(4);
  if (!_replayData["time"].empty()) {
    double data;
    std::string pidTableKey;
    int8_t success;
    int location = 0;
    if (timer == nullptr) {
      qDebug("Signal from QTimer not found");
      return;
    } else if (&timer == &timer26) { // push speed, rpm, and throttle to middleware
      data = _replayData["speed"][location];
      pidTableKey = "SPEED";
      success = PublishToMiddleware(buffMan, data, pidTableKey);

      data = _replayData["rpms"][location];
      pidTableKey = "RPM";
      success = PublishToMiddleware(buffMan, data, pidTableKey);

      data = _replayData["throttle"][location];
      pidTableKey = "THROTTLE";
      success = PublishToMiddleware(buffMan, data, pidTableKey);

      //removeReplayDataFromFront("speed");
      //removeReplayDataFromFront("rpms");
      //removeReplayDataFromFront("throttle");
    } else if (&timer == &timer78) { // push gear to middlewear
      data = _replayData["gear"][location];
      pidTableKey = "GEAR";
      success = PublishToMiddleware(buffMan, data, pidTableKey);
      
      //removeReplayDataFromFront("gear");
    } else if (&timer == &timer20) { // reduce time to know when to stop timers
      //removeReplayDataFromFront("time");
      location++;
    }
  } else {
    timer26->stop();
    timer78->stop();
    timer20->stop();
  }
  // pop the most recent data and send it to BufferManager (no particular order)
}

/**
 * @brief starts the timers.
 * 
 */
void VehicleParser::replayStart(){
  this->timer26 = new QTimer(this); //! May need to remove the `this` object in QTimer() if there are issues
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
 * @brief starts the timers.
 * 
 */
void VehicleParser::replayStart(){
  this->timer26 = new QTimer(this); //! May need to remove the `this` object in QTimer() if there are issues
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
 * @brief starts the timers.
 * 
 */
void VehicleParser::replayStart(){
  this->timer26 = new QTimer(this); //! May need to remove the `this` object in QTimer() if there are issues
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
 * @brief starts the timers.
 * 
 */
void VehicleParser::replayStart(){
  this->timer26 = new QTimer(this); //! May need to remove the `this` object in QTimer() if there are issues
  connect(timer26, &QTimer::timeout, this, &VehicleParser::dataRegulator);
  timer26->start(26);

  this->timer78 = new QTimer(this);
  connect(timer78, &QTimer::timeout, this, &VehicleParser::dataRegulator);
  timer78->start(78);

  this->timer20 = new QTimer(this);
  connect(timer20, &QTimer::timeout, this, &VehicleParser::dataRegulator);
  timer20->start(20);
}

/// @brief Makes a request to the device
/// @param request
/// @return
/// NOTE: This should be run in its own thread since it will probably block
/// while waiting for a response from the vehicle. Add a timeout
std::optional<std::string> VehicleParser::Request(const std::string& request) {
  std::string code = _pidTable[request].first;
  QString obdCode = QString::fromStdString(code);
  
  connection->sendCommand(obdCode);
}

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

/// @brief Forms the OBD string to interface with the vehicle ECU.
/// @param serviceMode The service mode to be used (OBD2 Standard, SAEJ1979)
/// @param code The code to be used
/// @return The OBD string
/// @note - Are there beneficial purposes where knowing the serviceMode in the
/// response is useful? Need to investigate further.
std::string VehicleParser::FormRequestString(int& serviceMode,
                                             std::string& code) {
    return "";
  // return (std::string)serviceMode + code + "\r";
}

/// @brief Forms the OBD string to interface with the vehicle ECU.
/// @param code The code to be used
/// @return The OBD string
std::string VehicleParser::FormRequestString(std::string code) {
  return code + "\r";
}

/// @brief
/// @note Change implementation based on how the dongle device works -- if
/// there's some form of way to validate connection status we should return 1 or
/// -1 based on connection status
void VehicleParser::initOBDConnection() {
  // Write to

  // InsertFunctionNameHere(FormRequestString("RESET"))
  // InsertFunctionNameHere(FormRequestString("ECHOOFF"))     # Echo off
  // InsertFunctionNameHere(FormRequestString("NOLINEFEED"))     # No linefeeds
  // InsertFunctionNameHere(FormRequestString("NOSPACES"))     # No spaces
  // InsertFunctionNameHere(FormRequestString("AUTOPRTCL"))    # Auto protocol
  // InsertFunctionNameHere(FormRequestString("STOREDDTC"))       # Request DTCs
}

// @brief Publish to the middleware what an OBD query has returned.
// @param data
// @return Return 0 if successful, return a 1 if there's an issue.
// Need to validate if BuffMan is a valid CircularBufferManager object, but how?
int8_t VehicleParser::PublishToMiddleware(CircularBufferManager<int>& BuffMan,
                                          int& data, std::string& pidTableKey) {
  if (_pidTable.find(pidTableKey) == _pidTable.end()) {
    std::cout << "Key provided has no value in _pidTable.\n";
    return 1;
  }

  return BuffMan.publish(data, _pidTable[pidTableKey].second);
}

/// @brief Publish to the middleware what an OBD query has returned.
/// @param data
/// @return Return 0 if successful, return a 1 if there's an issue.
int8_t VehicleParser::PublishToMiddleware(CircularBufferManager<int>& BuffMan,
                                          double& data,
                                          std::string& pidTableKey) {
  if (_pidTable.find(pidTableKey) == _pidTable.end()) {
    std::cout << "Key provided has no value in _pidTable.\n";
    return 1;
  }

  return BuffMan.publish(data, _pidTable[pidTableKey].second);
}

std::pair<std::string, int> VehicleParser::getPIDTable(const std::string& key) {
  if (_pidTable.find(key) == _pidTable.end()) {
    std::cout << "Key provided to getPIDTAble() is invalid.";
    return {};
  }

  return _pidTable[key];
}

// /// @brief
// /// @param key
// /// @return
// std::pair<std::string, int> VehicleParser::accessPIDTable(const std::string
// key) {
//     if (_pidTable.find(pidTableKey) == _pidTable.end()) {
//         std::cout << "Key provided has no value in _pidTable.\n";
//         return 1;
//     }

//     return _pidTable[key];
// }

/**
 * @brief stages all the data files from their parent directory and calls them
 * to be loaded one-by-one.
 *
 * @tparam T
 * @param file
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
 * @tparam T
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

void VehicleParser::startReplay(QObject* parent = nullptr) {}

std::map<std::string, std::vector<double>>& VehicleParser::getData() {
  return _replayData;
}

/**
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