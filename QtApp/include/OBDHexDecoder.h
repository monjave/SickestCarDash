#ifndef OBDHEXDECODER_H
#define OBDHEXDECODER_H

#include <QObject>
#include <QStringList>
#include "OBDPIDRegistry.h"

/**
 * @brief Decodes raw OBD-II hex responses into numeric values and emits decoded data.
 */
class OBDHexDecoder : public QObject {
    Q_OBJECT
public:
    explicit OBDHexDecoder(QObject *parent = nullptr);

public slots:
    void rawHexReceived(const QString &rawHex);  
signals:
    void dataConverted(int buffIndex, double data);  

private:
    double decodePIDValue(OBDPID pid, const QStringList &dataBytes);
};

#endif // OBDHEXDECODER_H
