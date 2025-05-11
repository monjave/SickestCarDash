#ifndef REPLAYPARSER_H
#define REPLAYPARSER_H

#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <filesystem>
#include <sstream>

template <class T>
class ReplayParser {
 private:
  void loadSave(std::filesystem::path file);
  void readCSV(std::fstream& file);

  std::map<std::string, std::vector<double>> _replayData;

 public:
  ReplayParser(std::string filePath);
  void getValue();
  std::map<std::string, std::vector<double>>& getData();
  // void startReplay();  // change from void when decide how to deliver data
};

#endif  // REPLAYPARSER_H
