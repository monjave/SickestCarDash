// VehicleConnection.h
#ifndef VEHICLECONNECTION_H
#define VEHICLECONNECTION_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include <QTimer>
#include <QIODevice> // for testing

class VehicleConnection : public QObject {
    Q_OBJECT

public:
    explicit VehicleConnection(QObject *parent = nullptr);
    explicit VehicleConnection(QIODevice *device, QObject *parent = nullptr);
    
    void beginInitSequence();

signals:
    void initComplete();
    void errorOccurred(QString error);
    void rawHexReceived(QString &hex);  // New signal for clean hex

public slots:
    void sendCommand(const QString &command);
    void handleReadyRead();

private slots:
    void sendNextInitCommand();

private:
    QIODevice *serial;
    QByteArray buffer;
    QStringList initCommands;
    int cmdIndex;
    QTimer initTimer;

    void configureSerialPort();
    // helper to configure if using QSerialPort
};

#endif // VEHICLECONNECTION_H