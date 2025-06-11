#ifndef QSERIALPORT_H
#define QSERIALPORT_H

class QSerialPort : public QIODevice {
public:
    void setPortName(const QString &name);
    bool open(OpenMode mode);
    void setBaudRate(qint32 baudRate);
    void setDataBits(DataBits dataBits);
    void setParity(Parity parity);
    void setStopBits(StopBits stopBits);
    void setFlowControl(FlowControl flowControl);
};

#endif // QSERIALPORT_H
