#ifndef REPLAYPARSER_H
#define REPLAYPARSER_H

#include <fstream>
#include <iostream>
#include <map>
#include <vector>

template <class T>
class ReplayParser {
 private:
  void loadSave(std::fstream file);
  void readCSV(std::fstream file);

  std::map<std::string, std::vector<double>> _replayData;

 public:
  ReplayParser(std::string filePath);
  double getValue();
  // void startReplay();  // change from void when decide how to deliver data
};

#endif  // REPLAYPARSER_H
