#include "FrontendConnection.h"

FrontendConnection::FrontendConnection(CircularBufferManagerWrapper *newDataProperties, QObject* parent) : QObject(parent),
    carData(new VehicleParser(_replayPath)), dataProperties(newDataProperties) {

    // Connect start button to replayStart method
    // connect(this, &CircularBufferManagerWrapper::insertSignal, carData, &VehicleParser::replayStart);
    connect(carData, &VehicleParser::dataReady, this, &FrontendConnection::dataReady);
}

FrontendConnection::~FrontendConnection() {
    delete carData;
    delete dataProperties;
}

CircularBufferManagerWrapper* FrontendConnection::data() const {
    return dataProperties;
}

Q_INVOKABLE void FrontendConnection::togglePaused() {
    emit startReplay();
}

void FrontendConnection::startReplay() {
    qDebug() << "Working dir:" << QDir::currentPath();
    carData->replayStart();
}

void FrontendConnection::dataReady(int buffNum, double value) {
    switch(buffNum) {
    case 0:
        dataProperties->setSpeed(value);
        break;
    case 1:
        dataProperties->setRPM(value);
        break;
    case 2:
        dataProperties->setFuel(value);
        break;
    case 3:
        dataProperties->setCoolanttemp(value);
        break;
    case 4:
        dataProperties->setClock(value);
        break;
    case 5:
        dataProperties->setOilTemp(value);
        break;
    case 6:
        dataProperties->setGearShift(value);
        break;
    case 7:
        dataProperties->setABS(value);
        break;
    case 8:
        dataProperties->setVoltage(value);
        break;
    case 9:
        dataProperties->setSeatBelt(value);
        break;
    case 10:
        dataProperties->setEngineCheck(value);
        break;
    case 11:
        dataProperties->setHighlights(value);
        break;
    case 12:
        dataProperties->setParking(value);
        break;
    case 13:
        dataProperties->setTurnLeft(value);
        break;
    case 14:
        dataProperties->setTurnRight(value);
        break;
    }
}
