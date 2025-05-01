# ELM327 / AT Command Cheat Sheet (for SAE J1850 VPW)

This document outlines the basics for interfacing with the OBD-II system of our 
test vehicle, a 2004 Chevy Blazer, OBD-II system using ELM327-based adapters. 
These commands and code snippets help extract useful real-time data like RPM, 
speed, and engine temperature. General Motors used a proprietary protocol

---

## Setup Commands

Initialization commands sent over serial to the ELM327 adapter. Each command 
must be followed by a carriage return (`\r`):

| Command | Description |
|---------|-------------|
| `ATZ`   | Resets the adapter. Good to send first to ensure a clean session. |
| `ATE0`  | Turns echo off. Prevents the adapter from repeating back what you sent. |
| `ATL0`  | Turns off linefeeds in responses. Makes parsing easier. |
| `ATS0`  | Turns off spaces in responses. Also makes parsing easier. |
| `ATSP0` | Sets protocol to automatic. Lets the adapter auto-detect J1850 VPW. |

---

## Common OBD-II Data Requests

These are PID (Parameter ID) queries sent to the vehicle's ECU:

| Command | Description |
|---------|-------------|
| `010C`  | Request Engine RPM |
| `010D`  | Request Vehicle Speed |
| `0105`  | Request Coolant Temperature |
| `0111`  | Request Throttle Position |

---

## Example: Get RPM

**Send:** `010C\r`  
**Response:** `41 0C 1A F8`  
**Explanation:**
- `41` means the response is from Mode 01 (live data)
- `0C` is the PID for RPM
- `1A` and `F8` are the data bytes (A and B)  

**Formula:** `((A * 256) + B) / 4`  
**Result:** `(0x1A * 256 + 0xF8) / 4 = 1726 RPM`

---

## Example: Vehicle Speed

**Send:** `010D\r`  
**Response:** `41 0D 28`  
**Explanation:**
- `41` = Mode 01 response
- `0D` = PID for vehicle speed
- `28` = speed value in km/h (`0x28 = 40`)

---

## Example Code (C++)

```cpp
#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::fstream serial("/dev/ttyUSB0", std::ios::in | std::ios::out);

    if (!serial.is_open()) {
        std::cerr << "Failed to open serial port" << std::endl;
        return 1;
    }

    // Send initialization commands
    serial << "ATZ\r";
    serial << "ATE0\r";
    serial << "ATL0\r";
    serial << "ATS0\r";
    serial << "ATSP0\r";

    // Request RPM
    serial << "010C\r";

    std::string response;
    std::getline(serial, response);
    std::cout << "RPM Response: " << response << std::endl;

    return 0;
}
```
