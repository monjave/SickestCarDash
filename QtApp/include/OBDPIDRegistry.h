#ifndef OBDPIDREGISTRY_H
#define OBDPIDREGISTRY_H

#include <QString>
#include <QMap>

enum class OBDPID {
    SPEED,
    RPM,
    FUEL,
    COOLANT_TEMP,
    THROTTLE,
    OIL_TEMP,
    GEAR,
    BATTERY_VOLTAGE,
    STORED_DTC,
    UNKNOWN
};

class OBDPIDRegistry {
public:
    static OBDPID fromHex(const QString& hex);
    static QString toHex(OBDPID pid);
    static QString toName(OBDPID pid);
    static int toBufferIndex(OBDPID pid);

private:
    static const QMap<QString, OBDPID> hexToPid;
    static const QMap<OBDPID, QString> pidToHex;
    static const QMap<OBDPID, int> pidToIndex;
    static const QMap<OBDPID, QString> pidToName;
};

#endif // OBDPIDREGISTRY_H
