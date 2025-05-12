#include "VehicleParser.h"

// pidTable values come from https://en.wikipedia.org/wiki/OBD-II_PIDs#Service_03
VehicleParser::VehicleParser() {
    _pidTable = {
        // **** NOT IN BUFFER ****
        {"RESET"     , {"ATZ", -1}},
        {"ECHOOFF"   , {"ATE0", -1}},
        {"NOLINEFEED", {"ATL0", -1}},
        {"NOSPACES"  , {"ATS0", -1}},
        {"AUTOPRTCL" , {"ATSP0", -1}},
        // ***********************
        {"SPEED"     , {"010D", 0}},           // Buffer 0
        {"RPM"       , {"010C", 1}},           // Buffer 1
        {"FUEL"      , {"012F", 2}},           // Buffer 2
        {"WATERTEMP" , {"0105", 3}},           // Buffer 3
        {"THROTTLE"  , {"0111", 4}},           // Buffer 4
        {"OILTEMP"   , {"015C", 5}},           // Buffer 5
        {"GEAR"      , {"01A4", 6}},           // Buffer 6
        {"BATTVOLTS" , {"0142", 7}},           // Buffer 7
        {"STOREDDTC" , {"03"  , 8}}            // Buffer 8
    };
};

/// @brief Makes a request to the device 
/// @param request 
/// @return 
/// NOTE: This should be run in its own thread since it will probably block while waiting for a response from the vehicle. Add a timeout
std::optional<std::string> VehicleParser::Request(const std::string& request) {
    std::string code = _pidTable[request].first;

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
/// @note - Are there beneficial purposes where knowing the serviceMode in the response is useful? Need to investigate further.
std::string VehicleParser::FormRequestString(int& serviceMode, std::string& code) {
    // return (std::string)serviceMode + code + "\r";
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
    
    // InsertFunctionNameHere(FormRequestString("RESET"))
    // InsertFunctionNameHere(FormRequestString("ECHOOFF"))     # Echo off
    // InsertFunctionNameHere(FormRequestString("NOLINEFEED"))     # No linefeeds
    // InsertFunctionNameHere(FormRequestString("NOSPACES"))     # No spaces
    // InsertFunctionNameHere(FormRequestString("AUTOPRTCL"))    # Auto protocol
    // InsertFunctionNameHere(FormRequestString("STOREDDTC"))       # Request DTCs
}

/// @brief 
/// @param data 
/// @return 
int8_t VehicleParser::PublishToMiddleware(CircularBufferManager<int>& BuffMan, int& data) {
    // BuffMan.publish(data, )
}