// MockQSerialPort.cpp
#include "MockQSerialPort.h"

MockQSerialPort::MockQSerialPort(QObject *parent)
    : QIODevice(parent) {
    open(QIODevice::ReadWrite);
}

void MockQSerialPort::setResponse(const QStringList &response) {
    preprogrammedResponses = response;
}

void MockQSerialPort::simulateIncomingData(const QString &data) {
    incomingData.enqueue(data.toUtf8());
    emit readyRead();
}

bool MockQSerialPort::open(OpenMode mode) {
    isOpenFlag = true;
    QIODevice::open(mode);
    return true;
}

void MockQSerialPort::close() {
    isOpenFlag = false;
    QIODevice::close();
}

qint64 MockQSerialPort::readData(char *data, qint64 maxlen) {
    if (incomingData.isEmpty()) {
        return 0; // No data to read
    }
    QByteArray nextData = incomingData.dequeue();
    qint64 bytesToRead = std::min<qint64>(nextData.size(), maxlen);
    memcpy(data, nextData.constData(), bytesToRead);
    return bytesToRead;
}

qint64 MockQSerialPort::writeData(const char *data, qint64 len) {
    Q_UNUSED(data)
    Q_UNUSED(len)

    if (!preprogrammedResponses.isEmpty()) {
        QString reply = preprogrammedResponses.takeFirst();
        simulateIncomingData(reply + "\r");
    }

    return len;
}
