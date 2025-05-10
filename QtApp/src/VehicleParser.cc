#include "VehicleParser.h"

VehicleParser::VehicleParser() {
    pidRegistry = {
        "SPEED"     : "",           // Buffer 0
        "RPM"       : "",           // Buffer 1
        "FUEL"      : "",           // Buffer 2
        "WATERTEMP" : "",           // Buffer 3
        "OILTEMP"   : "",           // Buffer 4
        "GEAR"      : "",           // Buffer 5
        "BATTVOLTS" : "",           // Buffer 6
        "STOREDDTC" : "03",           // Buffer 7
    };
};

std::string VehicleParser::Request() {

    return "";
}

int VehicleParser::convertHexToInt() {

    return 0;
}

std::string VehicleParser::FormRequestString() {
    
}