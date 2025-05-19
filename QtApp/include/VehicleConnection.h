// VehicleConnection.h
#ifndef VEHICLECONNECTION_H
#define VEHICLECONNECTION_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include <QTimer>

class VehicleConnection : public QObject {
    Q_OBJECT

public:
    explicit VehicleConnection(QObject *parent = nullptr);
    void sendCommand(const QString &command);
    void beginInitSequence();

signals:
    
    void initComplete();
    void errorOccurred(QString error);
    void rawHexReceived(const QString &hex);  // New signal for clean hex

private slots:
    void handleReadyRead();
    void sendNextInitCommand();

private:
    QSerialPort *serial;
    QByteArray buffer;
    QStringList initCommands;
    int cmdIndex;
    QTimer initTimer;
};

#endif // VEHICLECONNECTION_H