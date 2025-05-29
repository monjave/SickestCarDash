// MockQSerialPort.h
#ifndef MOCKQSERIALPORT_H
#define MOCKQSERIALPORT_H

#include <QIODevice>
#include <QQueue>
#include <QStringList>

class MockQSerialPort : public QIODevice {
    Q_OBJECT

public:
    explicit MockQSerialPort(QObject *parent = nullptr);

    void setResponse(const QStringList &response);
    void simulateIncomingData(const QString &data);

    bool open(OpenMode mode) override;
    void close() override;

    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;

signals:
    void readyRead();

private:
    QQueue<QByteArray> incomingData;
    QStringList preprogrammedResponses;
    bool isOpenFlag = false;
};

#endif // MOCKQSERIALPORT_H