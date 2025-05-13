#include "ReplayParser.h"

#include <iostream>

/**
 * @brief Construct a new Replay Parser< T>:: Replay Parser object. Importantly,
 * you must provide it with the location of the immediate parent directory of
 * the telemetry files
 *
 * @tparam T
 * @param filePath
 */
template <class T>
ReplayParser<T>::ReplayParser(std::string filePath) {
  std::cout << "CWD: " << std::filesystem::current_path() << std::endl;

  std::filesystem::path directoryPath = filePath;

  if (!exists(directoryPath)) {
    throw std::invalid_argument("Invalid File Location");
  } else {
    loadSave(directoryPath);
  }
  getValue();
}

/**
 * @brief loads all the data files from their parent directory.
 *
 * @tparam T
 * @param file
 */
template <class T>
void ReplayParser<T>::loadSave(std::filesystem::path directoryPath) {
  for (const auto& fileName :
       std::filesystem::directory_iterator(directoryPath)) {
    std::filesystem::path filePath = fileName.path();
    std::cout << (filePath) << std::endl;
    std::fstream file(filePath.string());
    readCSV(file);
    file.close();
  }
}

/**
 * @brief
 *
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

    while (std::getline(stream, header, ',')) {
      headers.push_back(header);
      _replayData[header] = {};
    }

    while (std::getline(file, line)) {
      std::stringstream secondStream(line);
      std::string num;
      double double_value;
      int column = 0;

      while (std::getline(secondStream, num, ',')) {
        //! TESTING, DELETE START******************************
        try {
          double_value = std::stod(num);
        } catch (const std::invalid_argument& e) {
          std::cerr << "Invalid argument: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
          std::cerr << "Out of range: " << e.what() << std::endl;
        }
        //! TESTING, DELETE END******************************
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
void ReplayParser<T>::getValue() {
  // ! DELETE AFTER TESTING START**********************************

  std::string outputFilePath = "../../QtApp/test/build/Debug/test.txt.idea";

  size_t maxRowsPerColumn = 10;
  size_t tablePreviewRows = 5;

  std::ofstream out(outputFilePath);
  if (!out.is_open()) {
    std::cerr << "Failed to open output file: " << outputFilePath << std::endl;
    return;
  }

  for (const auto& column : _replayData) {
    out << std::left << std::setw(10) << "Column:" << std::setw(20)
        << column.first << "Rows: " << std::setw(10) << column.second.size()
        << std::endl;
  }
}
// ! DELETE AFTER TESTING END**********************************

template class ReplayParser<int>;
template class ReplayParser<uint8_t>;
template class ReplayParser<long>;
template class ReplayParser<long long>;
template class ReplayParser<float>;
template class ReplayParser<double>;
template class ReplayParser<std::string>;
template class ReplayParser<char>;