#include "CircularBufferManagerWrapper.h"

CircularBufferManagerWrapper::CircularBufferManagerWrapper(QObject *parent) : QObject(parent) {

    //timer = new QTimer(this);
    //timerIcons = new QTimer(this);
    //qDebug() << "Working dir:" << QDir::currentPath();
    // Connect start button to replayStart method
    // connect(this, &CircularBufferManagerWrapper::insertSignal, carData, &VehicleParser::replayStart);
    //connect(carData, &VehicleParser::dataReady, this, &CircularBufferManagerWrapper::dataReady);
    //connect(timer, &QTimer::timeout, this, &CircularBufferManagerWrapper::increment);
    //connect(timerIcons, &QTimer::timeout, this, &CircularBufferManagerWrapper::geartime);
}

/*CircularBufferManagerWrapper::~CircularBufferManagerWrapper() {
    delete carData;
}*/

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
};

void CircularBufferManagerWrapper::setFuel(double newFuel) {
    if (newFuel != m_fuel) {
        m_fuel = newFuel;
        emit fuelChanged();
    }
};

void CircularBufferManagerWrapper::setTemp(double newTemp) {
    if (newTemp != m_temp) {
        m_temp = newTemp;
        emit tempChanged();
    }
};

void CircularBufferManagerWrapper::setCoolanttemp(double newCoolanttemp) {
    if (newCoolanttemp != m_coolanttemp) {
        m_coolanttemp = newCoolanttemp;
        emit coolanttempChanged();
    }
};

void CircularBufferManagerWrapper::setClock(double newClock) {
    if (newClock != m_clock) {
        m_clock = newClock;
        emit clockChanged();
    }
};

void CircularBufferManagerWrapper::setEnginetemp(double newEnginetemp) {
    if (newEnginetemp != m_enginetemp) {
        m_enginetemp = newEnginetemp;
        emit enginetempChanged();
    }
};

void CircularBufferManagerWrapper::setOilTemp(double newOilTemp) {
    if (newOilTemp != m_oiltemp) {
        m_oiltemp = newOilTemp;
        emit oilTempChanged();   }
};

void CircularBufferManagerWrapper::setGearShift(double newGearShift) {
    if (newGearShift != m_gearshift) {
        m_gearshift = newGearShift;
        emit gearshiftChanged();
    }
};

void CircularBufferManagerWrapper::setSeatBelt(bool newSeatBelt) {
    if (m_seatbelt != newSeatBelt) {
        m_seatbelt = newSeatBelt;
        emit seatbeltChanged();
    }
};

void CircularBufferManagerWrapper::setHighlights(bool newHighlights) {
    if (m_highlights != newHighlights) {
        m_highlights = newHighlights;
        emit highlightsChanged();
    }
};

void CircularBufferManagerWrapper::setABS(bool newABS) {
    if (m_abs != newABS) {
        m_abs = newABS;
        emit absChanged();
    }
};

void CircularBufferManagerWrapper::setEngineCheck(bool newEngineCheck) {
    if (m_enginecheck != newEngineCheck) {
        m_enginecheck = newEngineCheck;
        emit enginecheckChanged();
    }
};

void CircularBufferManagerWrapper::setParking(bool newParking) {
    if (m_parking != newParking) {
        m_parking = newParking;
        emit parkingChanged();
    }
};

/*Q_INVOKABLE void CircularBufferManagerWrapper::togglePaused() {
    emit startReplay();

    if (timer->isActive()) {
            timer->stop();
        } else {
        timer->start(1500);
        }

        if (timerIcons->isActive()) {
            timerIcons->stop();
        } else {
            timerIcons->start(500);
        }
};

void CircularBufferManagerWrapper::increment() {
    // qDebug() << "Working dir:" << QDir::currentPath();
    // VehicleParser* carData = new VehicleParser(_replayPath);
    // carData->replayStart();

    if (m_speed >= 140) m_speed = 0;
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
        emit parkingChanged();

}

void CircularBufferManagerWrapper::geartime() {
    if (m_gearshift >= 9) {
            m_gearshift = 0;
        } else {
        m_gearshift++;
        }
        emit gearshiftChanged();
}

void CircularBufferManagerWrapper::startReplay() {
    qDebug() << "Working dir:" << QDir::currentPath();
    carData->replayStart();
}

void CircularBufferManagerWrapper::dataReady(int buffNum, double value) {
    switch(buffNum) {
    case 0:
        setSpeed(value);
        break;
    case 1:
        setRPM(value);
        break;
    case 2:
        setFuel(value);
        break;
    case 3:
        setCoolanttemp(value);
        break;
    case 4:
        setClock(value);
        break;
    case 5:
        setOilTemp(value);
        break;
    case 6:
        setGearShift(value);
        break;
    case 7:
        setABS(value);
        break;
    case 8:
        break;
    }
} */
