#include "CircularBufferManagerWrapper.h"

CircularBufferManagerWrapper::CircularBufferManagerWrapper(QObject *parent) : QObject(parent), m_speed(0), m_rpm(0), m_fuel(0),
    m_voltage(9), m_coolanttemp(100), m_clock(0), m_enginetemp(0), m_oiltemp(0), m_gearshift(0), m_seatbelt(0), m_highlights(0),
    m_abs(0), m_enginecheck(0), m_parking(0), m_turnleft(0), m_turnright(0) {

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

double CircularBufferManagerWrapper::voltage() const {
    return m_voltage;
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

double CircularBufferManagerWrapper::turnleft() const {
    return m_turnleft;
}

double CircularBufferManagerWrapper::turnright() const {
    return m_turnright;
}

void CircularBufferManagerWrapper::setSpeed(double newSpeed) {
    if (newSpeed != m_speed) {
        m_speed = newSpeed;
        emit speedChanged();
    }
}

void CircularBufferManagerWrapper::setRPM(double newRPM) {
    if (newRPM != m_rpm) {
        m_rpm = newRPM;
        emit rpmChanged();
    }
}

void CircularBufferManagerWrapper::setFuel(double newFuel) {
    if (newFuel != m_fuel) {
        m_fuel = newFuel;
        emit fuelChanged();
    }
}

void CircularBufferManagerWrapper::setVoltage(double newVoltage) {
    if (newVoltage != m_voltage) {
        m_voltage = newVoltage;
        emit voltageChanged();
    }
}

void CircularBufferManagerWrapper::setCoolanttemp(double newCoolanttemp) {
    if (newCoolanttemp != m_coolanttemp) {
        m_coolanttemp = newCoolanttemp;
        emit coolanttempChanged();
    }
}

void CircularBufferManagerWrapper::setClock(double newClock) {
    if (newClock != m_clock) {
        m_clock = newClock;
        emit clockChanged();
    }
}

void CircularBufferManagerWrapper::setEnginetemp(double newEnginetemp) {
    if (newEnginetemp != m_enginetemp) {
        m_enginetemp = newEnginetemp;
        emit enginetempChanged();
    }
}

void CircularBufferManagerWrapper::setOilTemp(double newOilTemp) {
    if (newOilTemp != m_oiltemp) {
        m_oiltemp = newOilTemp;
        emit oilTempChanged();   }
}

void CircularBufferManagerWrapper::setGearShift(double newGearShift) {
    if (newGearShift != m_gearshift) {
        m_gearshift = newGearShift;
        emit gearshiftChanged();
    }
}

void CircularBufferManagerWrapper::setSeatBelt(double newSeatBelt) {
    if (m_seatbelt != newSeatBelt) {
        m_seatbelt = newSeatBelt;
        emit seatbeltChanged();
    }
}

void CircularBufferManagerWrapper::setHighlights(double newHighlights) {
    if (m_highlights != newHighlights) {
        m_highlights = newHighlights;
        emit highlightsChanged();
    }
}

void CircularBufferManagerWrapper::setABS(double newABS) {
    if (m_abs != newABS) {
        m_abs = newABS;
        emit absChanged();
    }
}

void CircularBufferManagerWrapper::setEngineCheck(double newEngineCheck) {
    if (m_enginecheck != newEngineCheck) {
        m_enginecheck = newEngineCheck;
        emit enginecheckChanged();
    }
}

void CircularBufferManagerWrapper::setParking(double newParking) {
    if (m_parking != newParking) {
        m_parking = newParking;
        emit parkingChanged();
    }
}

void CircularBufferManagerWrapper::setTurnLeft(double newTurnLeft) {
    if (m_turnleft != newTurnLeft) {
        m_turnleft = newTurnLeft;
        emit turnLeftChanged();
    }
}

void CircularBufferManagerWrapper::setTurnRight(double newTurnRight) {
    if (m_turnright != newTurnRight) {
        m_turnright = newTurnRight;
        emit turnRightChanged();
    }
}
