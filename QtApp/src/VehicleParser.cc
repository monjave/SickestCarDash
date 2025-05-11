#include "VehicleParser.h"

// pidTable values come from https://en.wikipedia.org/wiki/OBD-II_PIDs#Service_03
VehicleParser::VehicleParser() {
    _pidTable = {
        // **** NOT IN BUFFER ****
        {"RESET"     , "ATZ"},
        {"ECHO OFF"  , "ATE0"},
        {"NOLINEFEED", "ATL0"},
        {"NOSPACES"  , "ATS0"},
        {"AUTOPRTCL" , "ATSP0"},
        // ***********************
        {"SPEED"     , "010D"},           // Buffer 0
        {"RPM"       , "010C"},           // Buffer 1
        {"FUEL"      , "012F"},           // Buffer 2
        {"WATERTEMP" , "0105"},           // Buffer 3
        {"THROTTLE"  , "0111"},           // Buffer 4
        {"OILTEMP"   , "015C"},           // Buffer 5
        {"GEAR"      , "01A4"},           // Buffer 6
        {"BATTVOLTS" , "0142"},           // Buffer 7
        {"STOREDDTC" , "03"},             // Buffer 8
    };
};

/// @brief Makes a request to the device 
/// @param request 
/// @return 
/// NOTE: This should be run in its own thread since it will probably block while waiting for a response from the vehicle
std::optional<std::string> VehicleParser::Request(const std::string& request) {
    std::string code = _pidTable[request];

    /* TODO
        Insert logic once we know what device we're running with
    */

    return code;
}

/// @brief Extracts the last two bytes of the response data from the vehicle
/// @param hexString 
/// @return Returns an integer with the last two bytes of the response data. Returns std::nullopt if conversion doesn't work
std::optional<int> VehicleParser::ExtractData(const std::string& hexString) {
    try {
        size_t processed = 0;
        int value = std::stoi(hexString, &processed, 16);

        if (processed != hexString.size()) {
            return std::nullopt;
        }

        value &= 0xFF;
        
        return value;
    } catch (const std::exception& e) {
        std::cerr << "Hex conversion error: " << e.what() << '\n';
        return std::nullopt;
    }
}


/// @brief Forms the OBD string to interface with the vehicle ECU.
/// @param serviceMode The service mode to be used (OBD2 Standard, SAEJ1979)
/// @param code The code to be used
/// @return The OBD string
std::string VehicleParser::FormRequestString(int serviceMode, std::string code) {

}

/// @brief Forms the OBD string to interface with the vehicle ECU.
/// @param code The code to be used
/// @return The OBD string
std::string VehicleParser::FormRequestString(std::string code) {
    return code + "\r";
}

/// @brief 
/// @note Change implementation based on how the dongle device works -- if there's some form of way to validate connection status we should return 1 or -1 based on connection status
void VehicleParser::initOBDConnection() {
    // Write to 
    // InsertFunctionNameHere("ATZ\r")      # Reset
    // InsertFunctionNameHere("ATE0\r")     # Echo off
    // InsertFunctionNameHere("ATL0\r")     # No linefeeds
    // InsertFunctionNameHere("ATS0\r")     # No spaces
    // InsertFunctionNameHere("ATSP0\r")    # Auto protocol
    // InsertFunctionNameHere("03\r")       # Request DTCs
}