#include "ReplayParser.h"

/**
 * @brief Construct a new Replay Parser< T>:: Replay Parser object
 * 
 * @tparam T 
 * @param filePath 
 */
template <class T>
ReplayParser<T>::ReplayParser(std::string filePath){
  _replayData["hello"] = {0, 1, 2, 3};

  std::cout << "CWD: " << std::filesystem::current_path() << std::endl;

  std::filesystem::path directoryPath = filePath;

  loadSave(directoryPath);

  if(!exists(directoryPath)){
    throw std::invalid_argument("Invalid File Location");
  } else {
    loadSave(directoryPath);
  }
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param file 
 */
template <class T>
void ReplayParser<T>::loadSave(std::filesystem::path directoryPath) {

  for(const auto &fileName : std::filesystem::directory_iterator(directoryPath)){
    std::filesystem::path filePath = fileName.path();
    std::cout << (filePath) << std::endl;
    std::fstream file(filePath.string());
    readCSV(file);
    file.close();
  }
}

template <class T>
void ReplayParser<T>::readCSV(std::fstream& file) {
  if(file.is_open()){
    std::vector<std::string> headers;
    std::string line;
    std::string header;
    std::getline(file, line);
    std::stringstream stream(line);

    while(std::getline(stream, header, ',')){
      headers.push_back(header);
      _replayData[header] = {};
    } 

    while(std::getline(file, line)){

    }
  } else {
    file.close();
    throw std::invalid_argument("file could not open");
  }
  file.close();
}

template <class T>
double ReplayParser<T>::getValue() {
  return 3.0;
}

template class ReplayParser<int>;
template class ReplayParser<uint8_t>;
template class ReplayParser<long>;
template class ReplayParser<long long>;
template class ReplayParser<float>;
template class ReplayParser<double>;
template class ReplayParser<std::string>;
template class ReplayParser<char>;