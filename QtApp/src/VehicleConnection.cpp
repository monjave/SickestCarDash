// VehicleConnection.cpp
#include "VehicleConnection.h"
#include <QDebug>

VehicleConnection::VehicleConnection(QObject *parent)
    : QObject(parent), serial(new QSerialPort(this)), cmdIndex(0) {

    serial->setPortName("/dev/ttyUSB0");
    serial->setBaudRate(QSerialPort::Baud38400);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (!serial->open(QIODevice::ReadWrite)) {
        emit errorOccurred("Failed to open serial port: " + serial->errorString());
        return;
    }

    connect(serial, &QSerialPort::readyRead, this, &VehicleConnection::handleReadyRead);
    connect(&initTimer, &QTimer::timeout, this, &VehicleConnection::sendNextInitCommand);

    initCommands = {"ATZ", "ATE0", "ATL0", "ATS0", "ATSP2"};
}

void VehicleConnection::sendCommand(const QString &command) {
    if (serial->isOpen()) {
        QString fullCommand = command + "\r";
        serial->write(fullCommand.toUtf8());
    }
}

void VehicleConnection::beginInitSequence() {
    cmdIndex = 0;
    initTimer.start(1000);  // Send each command 1 second apart
}

void VehicleConnection::sendNextInitCommand() {
    if (cmdIndex < initCommands.size()) {
        sendCommand(initCommands[cmdIndex++]);
    } else {
        initTimer.stop();
        emit initComplete();
    }
}

void VehicleConnection::handleReadyRead() {
    buffer.append(serial->readAll());

    if (buffer.contains("\r")) {
        QString response = QString::fromUtf8(buffer).trimmed();
        emit responseReceived(response);
        buffer.clear();
    }
}
