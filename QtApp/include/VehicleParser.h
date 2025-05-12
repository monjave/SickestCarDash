#ifndef VEHICLEPARSER_H
#define VEHICLEPARSER_H

#include "CircularBufferManager.h"
#include <unordered_map>
#include <string>


class VehicleParser {
private:
    // Map command names to PID strings and their assigned buffer in the BufferManager.
    std::unordered_map<std::string, std::pair<std::string, int>> _pidTable;

    std::string FormRequestString(int& serviceMode, std::string& code);
    std::string FormRequestString(std::string code);
    void initOBDConnection();
    
    public:
    VehicleParser();
    int8_t PublishToMiddleware(CircularBufferManager<int>& BuffMan, int& data, std::string& pidTableKey);
    std::optional<std::string> Request(const std::string& request); 
    std::optional<int> ExtractData(const std::string& hexString);
};

#endif