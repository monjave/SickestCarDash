#ifndef VEHICLEPARSER_H
#define VEHICLEPARSER_H

#include <unordered_map>
#include "CircularBufferManager.h"

class VehicleParser {
private:
    std::unordered_map<std::string, int> pidRegistry;

public:
    VehicleParser();
    std::string Request(); 
    int convertHexToInt();
};

#endif