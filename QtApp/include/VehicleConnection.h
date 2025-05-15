// VehicleConnection.h
#ifndef VEHICLECONNECTION_H
#define VEHICLECONNECTION_H

#include <QObject>
#include <QSerialPort>
#include <QTimer>

class VehicleConnection : public QObject {
    Q_OBJECT

public:
    explicit VehicleConnection(QObject *parent = nullptr);
    void sendCommand(const QString &command);
    void beginInitSequence();

signals:
    void responseReceived(QString response);
    void initComplete();
    void errorOccurred(QString error);

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