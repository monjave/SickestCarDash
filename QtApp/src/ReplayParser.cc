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

  std::fstream file(filePath);
  


  file.close();
}

template <class T>
void ReplayParser<T>::loadSave(std::fstream file) {


}

template <class T>
void ReplayParser<T>::readCSV(std::fstream file) {}

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