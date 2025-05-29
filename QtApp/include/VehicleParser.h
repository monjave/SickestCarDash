#ifndef VEHICLEPARSER_H
#define VEHICLEPARSER_H

#include <QDebug>
#include <QObject>
#include <QTimer>
#include <filesystem>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "CircularBufferManager.h"
#include "VehicleConnection.h"

class VehicleParser : public QObject {
  Q_OBJECT

 public slots:
  void dataRegulator();
  
 private:
  // Map command names to PID strings and their assigned buffer in the
  // BufferManager.
  std::unordered_map<std::string, std::pair<std::string, int>> _pidTable;
  // Map replay data names to the ordered vectors of their data
  std::map<std::string, std::vector<double>> _replayData;
  QTimer* timer26;
  QTimer* timer78;
  QTimer* timer20;

  void loadSave(std::filesystem::path file);
  void readCSV(std::fstream& file);
  void initOBDConnection();
  void loadPidTable();
  void removeReplayDataFromFront(std::string key);

 public:
  explicit VehicleParser();
  explicit VehicleParser(std::string filePath, QObject* parent = nullptr);

  int8_t PublishToMiddleware(CircularBufferManager<int>& BuffMan, int& data,
                            std::string& pidTableKey);
  int8_t PublishToMiddleware(CircularBufferManager<int>& BuffMan, double& data,
                             std::string& pidTableKey);
  void Request(VehicleConnection* connection, const std::string& request);
  std::pair<bool, int> ExtractData(const std::string& hexString);
  std::pair<std::string, int> getPIDTable(const std::string& key);
  void printValueToFile(std::string desiredFileLocation);
  std::map<std::string, std::vector<double>>& getData();
  void startReplay(QObject* parent);
  // std::pair<std::string, int> accessPIDTable(const std::string key);
};

#endif
