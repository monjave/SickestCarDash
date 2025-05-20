#ifndef VEHICLEPARSER_H
#define VEHICLEPARSER_H

#include "CircularBufferManager.h"
#include <unordered_map>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <filesystem>
#include <sstream>
#include <QObject>

class VehicleParser : public QObject {
    Q_OBJECT

private:
    // Map command names to PID strings and their assigned buffer in the BufferManager.
    std::unordered_map<std::string, std::pair<std::string, int>> _pidTable;
    // Map replay data names to the ordered vectors of their data
    std::map<std::string, std::vector<double>> _replayData;

    std::string FormRequestString(int& serviceMode, std::string& code);
    std::string FormRequestString(std::string code);
    void loadSave(std::filesystem::path file);
    void readCSV(std::fstream& file);
    void initOBDConnection();
    
public:
    explicit VehicleParser(QObject* parent = nullptr);
    VehicleParser(std::string filePath);
    int8_t PublishToMiddleware(CircularBufferManager<int>& BuffMan, int& data, std::string& pidTableKey);
    std::optional<std::string> Request(const std::string& request); 
    std::optional<int> ExtractData(const std::string& hexString);
    std::pair<std::string, int> getPIDTable(const std::string& key);
    void printValueToFile(std::string desiredFileLocation);
    std::map<std::string, std::vector<double>>& getData();
    // std::pair<std::string, int> accessPIDTable(const std::string key);
signals:

private slots:

};

#endif