#include "OBDHexDecoder.h"
#include <QDebug>

OBDHexDecoder::OBDHexDecoder(QObject *parent)
    : QObject(parent) {}

void OBDHexDecoder::rawHexReceived(const QString &rawHex) {
    QStringList bytes = rawHex.split(" ", Qt::SkipEmptyParts);
    if (bytes.size() < 3 || bytes[0] != "41") return;  // 41 = Mode 1 response

    QString pidHex = bytes[1].toUpper();
    OBDPID pid = OBDPIDRegistry::fromHex(pidHex);
    if (pid == OBDPID::UNKNOWN) {
        qDebug() << "Unknown PID:" << pidHex;
        return;
    }

    int bufferIndex = OBDPIDRegistry::toBufferIndex(pid);
    if (bufferIndex == -1) return;

    QStringList dataBytes = bytes.mid(2);  // A, B, etc.
    double value = decodePidValue(pid, dataBytes);
    emit dataConverted(bufferIndex, value);
}

double OBDHexDecoder::decodePidValue(OBDPID pid, const QStringList &dataBytes) {
    bool ok;

    switch (pid) {
        case OBDPID::SPEED: { //TODO will have this be toggleable in settings later
            double kmh = dataBytes[0].toInt(&ok, 16);
            return kmh * 0.621371;  // Convert km/h to mph
        }

        case OBDPID::RPM:
            if (dataBytes.size() >= 2) {
                int A = dataBytes[0].toInt(&ok, 16);
                int B = dataBytes[1].toInt(&ok, 16);
                double rpm = ((A * 256) + B) / 4.0;
                return rpm;  
            }
            break;

        case OBDPID::FUEL: {
            double fuelLevel = dataBytes[0].toInt(&ok, 16);
            return fuelLevel * 100.0 / 255.0;  
        }

        case OBDPID::THROTTLE: {
            return dataBytes[0].toInt(&ok, 16) * 100.0 / 255.0;
        }

        case OBDPID::COOLANT_TEMP: {
            double coolantTemp = dataBytes[0].toInt(&ok, 16) - 40;
            return coolantTemp;
        }

        case OBDPID::OIL_TEMP: {
            double oilTemp = dataBytes[0].toInt(&ok, 16) - 40;
            return oilTemp;
        }

        case OBDPID::GEAR: {
            return dataBytes[0].toInt(&ok, 16);  
        }

        case OBDPID::BATTERY_VOLTAGE:
            if (dataBytes.size() >= 2) {
                int A = dataBytes[0].toInt(&ok, 16);
                int B = dataBytes[1].toInt(&ok, 16);
                return ((A * 256) + B) / 1000.0; 
            }
            break;

        case OBDPID::STORED_DTC: {
            return 0;  
            // TODO: implement later for mvp just trigger check engine light on
            // then if we have time store code in settings page. -m
        }
        default:
            break;
    }

    return -1.0;  
}
