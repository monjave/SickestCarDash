#ifndef VEHICLEPARSER_H
#define VEHICLEPARSER_H

#include "CircularBufferManager.h"
#include <unordered_map>
#include <string>


class VehicleParser {
private:
    std::unordered_map<std::string, std::string> _pidTable;

    std::string FormRequestString(int serviceMode, std::string code);
    std::string FormRequestString(std::string code);
    void PublishToMiddleware(int data);

public:
    VehicleParser();
    std::optional<std::string> Request(const std::string& request); 
    std::optional<int> ExtractData(const std::string& hexString);
};

#endif