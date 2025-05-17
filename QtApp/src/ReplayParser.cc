#include "ReplayParser.h"

#include <chrono>
#include <iostream>

#include "CircularBufferManager.h"

/**
 * @brief Construct a new Replay Parser< T>:: Replay Parser object. Importantly,
 * you must provide it with the location of the immediate parent directory of
 * the telemetry files. This may take time to compile depending on the size of
 * the files being loaded.
 *
 * @tparam T
 * @param filePath
 */
template <class T>
ReplayParser<T>::ReplayParser(std::string filePath) {
  std::filesystem::path directoryPath = filePath;

  if (!exists(directoryPath)) {
    throw std::invalid_argument("Invalid File Location");
  } else {
    loadSave(directoryPath);
  }
}

/**
 * @brief stages all the data files from their parent directory and calls them
 * to be loaded one-by-one.
 *
 * @tparam T
 * @param file
 */
template <class T>
void ReplayParser<T>::loadSave(std::filesystem::path directoryPath) {
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
template <class T>
void ReplayParser<T>::readCSV(std::fstream& file) {
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
          throw std::invalid_argument("Invalid Argument: Unable to convert '" + num + "' to double.");
        } catch (const std::out_of_range& e) {
          throw std::invalid_argument("Out of Range: Value '" + num + "' is too large or too small to convert to double.");
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

template <class T>
std::map<std::string, std::vector<double>>& ReplayParser<T>::getData() {
  return _replayData;
}

template <class T>
void ReplayParser<T>::printValueToFile(std::string desiredFileLocation) {
  std::string outputFilePath = desiredFileLocation;

  std::ofstream file(outputFilePath);
  if (!file.is_open()) {
    std::cerr << "Failed to create or open file: " << outputFilePath
              << std::endl;
    return;
  }

  for (const auto& column : _replayData) {
    file << std::left << std::setw(10) << "Column:" << std::setw(20)
         << column.first << "Rows: " << std::setw(10) << column.second.size()<< "Values: "
         << std::endl;
  }
  file.close();
}

/**
 * @brief might not need this, tk still in development
 *
 * @tparam T
 * @param buffMan
 */
template <class T>
void ReplayParser<T>::publishToCircularBuffer(CircularBufferManager<int> buffMan) {
  std::vector<int> input = {1, 2, 3, 4, 5};
  buffMan.publish(input);
}

/**
 * @brief Starts the replay by deliberately and intermittently feeding the data
 * to the CircularBufferManager according to the time vector in _replayData.
 *
 * @tparam T
 */
template <class T>
void ReplayParser<T>::replayStart() {
  CircularBufferManager buffMan = CircularBufferManager<int>(5);
  publishToCircularBuffer(buffMan);
  // while replay is unfinished AND stopEarly flag is false:
  // publish() the most recent data to CircularBufferManager
  // stop when file is empty OR stopEarly flag is true
  // stopEarly flag maybe data driven? We just keep checking?
}

template class ReplayParser<int>;
template class ReplayParser<uint8_t>;
template class ReplayParser<long>;
template class ReplayParser<long long>;
template class ReplayParser<float>;
template class ReplayParser<double>;
template class ReplayParser<std::string>;
template class ReplayParser<char>;