#include "VehicleSystemManager.h"

VehicleSystemManager::VehicleSystemManager(QObject *parent)
    : QObject(parent),
        m_vc(new VehicleConnection(this)),
        m_poller(new PIDPoller(this)),
        m_decoder(new OBDHexDecoder(this)) {

    connect(m_poller, &PIDPoller::requestPid, 
            m_vc, &VehicleConnection::sendCommand);

    connect(m_vc, &VehicleConnection::rawHexReceived, 
            m_decoder,&OBDHexDecoder::rawHexReceived);

    connect(m_decoder, &OBDHexDecoder::dataConverted,
            this, &VehicleSystemManager::dataConverted);

    connect(m_vc, &VehicleConnection::initComplete,
            m_poller, &PIDPoller::startPolling);
}

void VehicleSystemManager::start() {
    m_vc->beginInitSequence();
}
