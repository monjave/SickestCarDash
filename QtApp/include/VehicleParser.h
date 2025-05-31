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
  void replayStart();
  void dataRegulator();

/*
For final implementation when actually communicating with the car
VehicleConnection's RawHexReceived -> intakeData()
receiveHex() -> ExtractData() -> sendToMiddle()
VehicleParser's sendToMiddle() -> publish to buffers
Middleware's dataReady() -> Frontend's something()

For replay implementation when only
Instantiate a VehicleParser object w/ directory location
VehicleParser fills out _replayData.
VehicleParser's replayStart() -> dataRegulator() -> publishToMiddleware()
Middleware's dataReady() -> Frontend's ReceiveData() and rest of Xavier's Frontend Implementation

2 Ways to do this:
Original implementation where we send a vector of all the data - This one is O(n)

OR

We have a dataReady() function that takes two parameters, buffNum and Value
Then we know exactly where to update  - This one is O(1)

CircularBufferWrapper: Create VehicleParser("file/location/")
connect to VehicleParser.replayStart()
call VehicleParser.replayStart()
*/

private slots:
    // void intakeData();

signals:
  // void dataReady();
  
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
  VehicleConnection* initOBDConnection();
  void loadPidTable();
  [[deprecated("Deletes values from _replayData")]]
  void removeReplayDataFromFront(std::string key);

public:
  explicit VehicleParser();
  explicit VehicleParser(std::string filePath, QObject* parent = nullptr);

  int8_t PublishToMiddleware(CircularBufferManager& BuffMan, int& data,
                            std::string& pidTableKey);
  int8_t PublishToMiddleware(CircularBufferManager& BuffMan, double& data,
                             std::string& pidTableKey);
  void Request(VehicleConnection* connection, const std::string& request);
  std::pair<bool, int> ExtractData(const std::string& hexString);
  std::pair<bool, int> ExtractData(const QString& hexString);
  std::pair<std::string, int> getPIDTable(const std::string& key);
  void printValueToFile(std::string desiredFileLocation);
  std::map<std::string, std::vector<double>>& getData();
  void startReplay(QObject* parent);
  // std::pair<std::string, int> accessPIDTable(const std::string key);
signals:

private slots:

};

#endif
