#ifndef REPLAYPARSER_H
#define REPLAYPARSER_H

#include <fstream>
#include <map>
#include <vector>
#include <iostream>

template <class T>
class ReplayParser {
  private:
  void loadSave(std::fstream file);
  void readCSV(std::fstream file);

  std::map<std::string, std::vector<double>> _replayData;

 public:
  ReplayParser(std::string filePath){
    _replayData["hello"] = {0, 1, 2, 3};
  };
  double getValue(){
    return 3.0;
  };
  //void startReplay();  // change from void when decide how to deliver data
};

#endif  // REPLAYPARSER_H