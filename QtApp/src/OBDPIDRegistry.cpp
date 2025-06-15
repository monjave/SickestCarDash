#include "OBDPIDRegistry.h"

const QMap<QString, OBDPID> OBDPIDRegistry::hexToPid = {
    {"0D", OBDPID::SPEED},
    {"0C", OBDPID::RPM},
    {"2F", OBDPID::FUEL},
    {"05", OBDPID::COOLANT_TEMP},
    {"11", OBDPID::THROTTLE},
    {"5C", OBDPID::OIL_TEMP},
    {"A4", OBDPID::GEAR},
    {"42", OBDPID::BATTERY_VOLTAGE},
    {"03", OBDPID::STORED_DTC}
};

const QMap<OBDPID, QString> OBDPIDRegistry::pidToHex = {
    {OBDPID::SPEED, "0D"},
    {OBDPID::RPM, "0C"},
    {OBDPID::FUEL, "2F"},
    {OBDPID::COOLANT_TEMP, "05"},
    {OBDPID::THROTTLE, "11"},
    {OBDPID::OIL_TEMP, "11 54"},
    {OBDPID::GEAR, "A4"},
    {OBDPID::BATTERY_VOLTAGE, "42"},
    {OBDPID::STORED_DTC, "03"}
};

const QMap<OBDPID, QString> OBDPIDRegistry::pidToName = {
    {OBDPID::SPEED, "Speed"},
    {OBDPID::RPM, "RPM"},
    {OBDPID::FUEL, "Fuel Level"},
    {OBDPID::COOLANT_TEMP, "Coolant Temp"},
    {OBDPID::THROTTLE, "Throttle"},
    {OBDPID::OIL_TEMP, "Oil Temp"},
    {OBDPID::GEAR, "Gear"},
    {OBDPID::BATTERY_VOLTAGE, "Battery Voltage"},
    {OBDPID::STORED_DTC, "Stored DTC"}
};

const QMap<OBDPID, int> OBDPIDRegistry::pidToIndex = {
    {OBDPID::SPEED, 0},
    {OBDPID::RPM, 1},
    {OBDPID::FUEL, 2},
    {OBDPID::COOLANT_TEMP, 3},
    {OBDPID::THROTTLE, 4},
    {OBDPID::OIL_TEMP, 5},
    {OBDPID::GEAR, 6},
    {OBDPID::BATTERY_VOLTAGE, 7},
    {OBDPID::STORED_DTC, 8}
};

OBDPID OBDPIDRegistry::fromHex(const QString& hex) {
    return hexToPid.value(hex.toUpper(), OBDPID::UNKNOWN);
}

QString OBDPIDRegistry::toHex(OBDPID pid) {
    return pidToHex.value(pid, "");
}

QString OBDPIDRegistry::toName(OBDPID pid) {
    return pidToName.value(pid, "Unknown");
}

int OBDPIDRegistry::toBufferIndex(OBDPID pid) {
    return pidToIndex.value(pid, -1);
}
