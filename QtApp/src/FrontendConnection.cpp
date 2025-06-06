#include "FrontendConnection.h"

FrontendConnection::FrontendConnection(QObject* parent) : QObject(parent), carData(new VehicleParser(_replayPath)),
    dataProperties(new CircularBufferManagerWrapper(this)) {

    //timer = new QTimer(this);
    //timerIcons = new QTimer(this);
    //qDebug() << "Working dir:" << QDir::currentPath();
    // Connect start button to replayStart method
    // connect(this, &CircularBufferManagerWrapper::insertSignal, carData, &VehicleParser::replayStart);
    //connect(carData, &VehicleParser::dataReady, this, &FrontendConnection::dataReady);
    //connect(timer, &QTimer::timeout, this, &CircularBufferManagerWrapper::increment);
    //connect(timerIcons, &QTimer::timeout, this, &CircularBufferManagerWrapper::geartime);
}

FrontendConnection::~FrontendConnection() {
    delete carData;
    //dataProperties = nullptr;
}

Q_INVOKABLE void FrontendConnection::togglePaused() {
    emit startReplay();

    /*if (timer->isActive()) {
            timer->stop();
        } else {
        timer->start(1500);
        }

        if (timerIcons->isActive()) {
            timerIcons->stop();
        } else {
            timerIcons->start(500);
        }*/
};

void FrontendConnection::increment() {
    // qDebug() << "Working dir:" << QDir::currentPath();
    // VehicleParser* carData = new VehicleParser(_replayPath);
    // carData->replayStart();

    /*if (m_speed >= 140) m_speed = 0;
        else m_speed += 10;

        if (m_rpm >= 7000) m_rpm = 0;
        else m_rpm += 1000;

        if (m_fuel >= 100) m_fuel = 0;
        else m_fuel += 10;

        if (m_temp >= 260) m_temp = 100;
        else m_temp += 40;

        if (m_oiltemp >= 80) m_oiltemp = 0;
        else m_oiltemp += 20;

        if (clock() >= 19999) {
            setClock(10000);
        } else {
        setClock(m_clock + 1);
        }

        m_seatbelt = !m_seatbelt;
        m_highlights = !m_highlights;
        m_abs = !m_abs;
        m_enginecheck = !m_enginecheck;
        m_parking = !m_parking;

        emit speedChanged();
        emit rpmChanged();
        emit fuelChanged();
        emit tempChanged();
        emit oilTempChanged();

        emit seatbeltChanged();
        emit highlightsChanged();
        emit absChanged();
        emit enginecheckChanged();
        emit parkingChanged(); */

}

void FrontendConnection::geartime() {
    /*if (m_gearshift >= 9) {
            m_gearshift = 0;
        } else {
        m_gearshift++;
        }
        emit gearshiftChanged();*/
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
        break;
    }
}
