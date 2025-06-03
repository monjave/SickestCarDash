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
#define BUFFERS_TO_INIT 9

#include "CircularBufferManager.h"
#include "VehicleConnection.h"

class VehicleParser : public QObject {
  Q_OBJECT

 public slots:
  void replayStart();
  void dataRegulator();

private slots:
    // void intakeData();

signals:
  void dataReady(int buffNum, double value);
  
private:
  // Map command names to PID strings and their assigned buffer in the
  // BufferManager.
  std::unordered_map<std::string, std::pair<std::string, int>> _pidTable;
  // Map replay data names to the ordered vectors of their data
  std::map<std::string, std::vector<double>> _replayData;
  QTimer* timer26;
  QTimer* timer78;
  QTimer* timer20;
  CircularBufferManager _buffMan = CircularBufferManager(BUFFERS_TO_INIT);
  int _location26;
  int _location78;
  int _location20;

  void loadSave(std::filesystem::path file);
  void readCSV(std::fstream& file);
  VehicleConnection* initOBDConnection();
  void loadPidTable();
  [[deprecated("Deletes values from _replayData")]]
  void removeReplayDataFromFront(std::string key);

public:
  explicit VehicleParser();
  explicit VehicleParser(std::string filePath, QObject* parent = nullptr);

  // int8_t PublishToMiddleware(CircularBufferManager& BuffMan, int& data,
  //                           std::string& pidTableKey);
  int8_t PublishToMiddleware(CircularBufferManager& BuffMan, double& data,
                             std::string& pidTableKey);
  void Request(VehicleConnection* connection, const std::string& request);
  std::pair<bool, int> ExtractData(const std::string& hexString);
  std::pair<bool, int> ExtractData(const QString& hexString);
  std::pair<std::string, int> getPIDTable(const std::string& key);
  void printValueToFile(std::string desiredFileLocation);
  std::map<std::string, std::vector<double>>& getData();
  double getValue(std::string key, int index);
  CircularBufferManager& getBufferManager();
  // std::pair<std::string, int> accessPIDTable(const std::string key);
signals:

private slots:

};

#endif
