#include "ReplayParser.h"

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

  loadSave(directoryPath);

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
      std::stringstream streamm(line);
      std::string num;
      int row = 0;

      while (getline(stream, num, ',')) {
        if (row < headers.size()) {
          double value = std::stod(num);
          _replayData[headers[row]].push_back(value);
        }
      }
    }
  } else {
    file.close();
    throw std::invalid_argument("file could not open");
  }
  file.close();
}

template <class T>
std::map<std::string, std::vector<double>>& ReplayParser<T>::getData() {
  return _replayData;
}

template <class T>
void ReplayParser<T>::getValue() {
  // ! DELETE AFTER TESTING**********************************

  std::string outputFilePath =
      "../../QtApp/replay/data/nurburgring_24h/data/file.txt";
  size_t maxRowsPerColumn = 10;
  size_t tablePreviewRows = 5;

  std::ofstream out(outputFilePath);
  if (!out.is_open()) {
    std::cerr << "Failed to open output file: " << outputFilePath << std::endl;
    return;
  }

  for (const auto& [column, values] : _replayData) {
    out << "column: " << column << " | rows: " << values.size() << "\n";

    size_t limit = std::min(tablePreviewRows, values.size());
    for (size_t i = 0; i < limit; ++i) {
      out << "  " << std::fixed << std::setprecision(8) << values[i] << "\n";
    }

    out << "\n";
  }
}
/*

  out << "== Summary by Column ==\n\n";

    for (const auto& [column, values] : _replayData) {
        out << "Column: " << column << "\n";
        size_t limit = std::min(maxRowsPerColumn, values.size());
        for (size_t i = 0; i < limit; ++i) {
            out << std::fixed << std::setprecision(8) << "  " << values[i] <<
  "\n";
        }
        out << "\n";
    }*/

// ! DELETE AFTER TESTING**********************************

template class ReplayParser<int>;
template class ReplayParser<uint8_t>;
template class ReplayParser<long>;
template class ReplayParser<long long>;
template class ReplayParser<float>;
template class ReplayParser<double>;
template class ReplayParser<std::string>;
template class ReplayParser<char>;