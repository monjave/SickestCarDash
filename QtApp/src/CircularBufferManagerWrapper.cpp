#include "CircularBufferManagerWrapper.h"

CircularBufferManagerWrapper::CircularBufferManagerWrapper(QObject *parent) : QObject(parent), m_speed(0),
    m_rpm(0), m_fuel(0), m_temp(100), m_coolanttemp(0), m_clock(10000), m_enginetemp(0), m_oiltemp(0), m_gearshift(0), m_seatbelt(true),
    m_highlights(true), m_abs(false), m_enginecheck(true), m_parking(true), carData(new VehicleParser(_replayPath))  {

    //timer = new QTimer(this);
    //timerIcons = new QTimer(this);
    //qDebug() << "Working dir:" << QDir::currentPath();
    // Connect start button to replayStart method
    // connect(this, &CircularBufferManagerWrapper::insertSignal, carData, &VehicleParser::replayStart);
    connect(carData, &VehicleParser::dataReady, this, &CircularBufferManagerWrapper::dataReady);
    //connect(timer, &QTimer::timeout, this, &CircularBufferManagerWrapper::increment);
    //connect(timerIcons, &QTimer::timeout, this, &CircularBufferManagerWrapper::geartime);
}

CircularBufferManagerWrapper::~CircularBufferManagerWrapper() {
    delete carData;
}

double CircularBufferManagerWrapper::speed() const {
    return m_speed;
}

double CircularBufferManagerWrapper::rpm() const {
    return m_rpm;
}

double CircularBufferManagerWrapper::fuel() const {
    return m_fuel;
}

double CircularBufferManagerWrapper::temp() const {
    return m_temp;
}

double CircularBufferManagerWrapper::coolanttemp() const {
    return m_coolanttemp;
}

double CircularBufferManagerWrapper::clock() const {
    return m_clock;
}

double CircularBufferManagerWrapper::enginetemp() const {
    return m_enginetemp;
}

double CircularBufferManagerWrapper::oiltemp() const {
    return m_oiltemp;
}

double CircularBufferManagerWrapper::gearshift() const {
    return m_gearshift;
}

double CircularBufferManagerWrapper::seatbelt() const {
    return m_seatbelt;
}

double CircularBufferManagerWrapper::highlights() const {
    return m_highlights;
}

double CircularBufferManagerWrapper::abs() const {
    return m_abs;
}

double CircularBufferManagerWrapper::enginecheck() const {
    return m_enginecheck;
}

double CircularBufferManagerWrapper::parking() const {
    return m_parking;
}
