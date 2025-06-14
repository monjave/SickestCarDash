#ifndef VEHICLESYSTEMMANAGER_H
#define VEHICLESYSTEMMANAGER_H

#include <QObject>
#include "VehicleConnection.h"
#include "PIDPoller.h"
#include "OBDHexDecoder.h"

class VehicleSystemManager : public QObject {
    Q_OBJECT

public: 
    explicit VehicleSystemManager(QObject *parent = nullptr);
    
    void start();

signals:
    void dataConverted(int buffIndex, double data);

private:
    VehicleConnection *m_vc;
    PIDPoller *m_poller;
    OBDHexDecoder *m_decoder;

};

#endif // VEHICLESYSTEMMANAGER_H