#include "VehicleSystemManager.h"

VehicleSystemManager::VehicleSystemManager(QObject *parent)
    : QObject(parent),
        m_vc(new VehicleConnection(this)),
        m_poller(new PIDPoller(this)),
        m_decoder(new OBDHexDecoder(this)) {

    connect(m_poller, &PIDPoller::requestPid, 
            m_vc, &VehicleConnection::sendCommand);
        qDebug() << "PIDPoller::requestPid connected to VehicleConnection::sendCommand";
    connect(m_vc, &VehicleConnection::rawHexReceived, 
            m_decoder,&OBDHexDecoder::rawHexReceived);
        qDebug() << "VehicleConnection::rawHexReceived connected to OBDHexDecoder::rawHexReceived";
    connect(m_decoder, &OBDHexDecoder::dataConverted,
            this, &VehicleSystemManager::dataConverted);
        qDebug() << "OBDHexDecoder::dataConverted connected to VehicleSystemManager::dataConverted";
    connect(m_vc, &VehicleConnection::initComplete,
            m_poller, &PIDPoller::onInitComplete);
        qDebug() << "VehicleConnection::initComplete connected to PIDPoller::onInitComplete";
}

void VehicleSystemManager::start() {
    m_vc->beginInitSequence();
}