#ifndef CIRCULARBUFFERMANAGERWRAPPER_H
#define CIRCULARBUFFERMANAGERWRAPPER_H

#include <QObject>
#include <QDir>
#include <QTimer>
#include "CircularBufferManager.h"
#include "VehicleParser.h"

class CircularBufferManagerWrapper : public QObject {
    Q_OBJECT
    Q_PROPERTY(double speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(double rpm READ rpm WRITE setRPM NOTIFY rpmChanged)
    Q_PROPERTY(double fuel READ fuel WRITE setFuel NOTIFY fuelChanged)
    Q_PROPERTY(double temp READ temp WRITE setTemp NOTIFY tempChanged)
    Q_PROPERTY(double coolanttemp READ coolanttemp WRITE setCoolanttemp NOTIFY coolanttempChanged)
    Q_PROPERTY(double clock READ clock WRITE setClock NOTIFY clockChanged)
    Q_PROPERTY(double enginetemp READ enginetemp WRITE setEnginetemp NOTIFY enginetempChanged)
    Q_PROPERTY(double oiltemp READ oiltemp WRITE setOilTemp NOTIFY oilTempChanged)

    Q_PROPERTY(double gearshift READ gearshift WRITE setGearShift NOTIFY gearshiftChanged)

    Q_PROPERTY(bool seatbelt READ seatbelt WRITE setSeatBelt NOTIFY seatbeltChanged)
    Q_PROPERTY(bool highlights READ highlights WRITE setHighlights NOTIFY highlightsChanged)
    Q_PROPERTY(bool abs READ abs WRITE setABS NOTIFY absChanged)
    Q_PROPERTY(bool enginecheck READ enginecheck WRITE setEngineCheck NOTIFY enginecheckChanged)
    Q_PROPERTY(bool parking READ parking WRITE setParking NOTIFY parkingChanged)

public:
    explicit CircularBufferManagerWrapper(QObject *parent = nullptr) : QObject(parent), m_speed(0),
        m_rpm(0), m_fuel(0), m_temp(100), m_coolanttemp(0), m_clock(10000), m_enginetemp(0), m_oiltemp(0), m_gearshift(0), m_seatbelt(true),
        m_highlights(true), m_abs(true), m_enginecheck(true), m_parking(true) {
        timer = new QTimer(this);
        timerIcons = new QTimer(this);
        VehicleParser* carData = new VehicleParser("../../../QtApp/replay/data/example_nurburgring_24h/data");
        //qDebug() << "Working dir:" << QDir::currentPath();
        carData->replayStart(); 
        // Connect start button to replayStart method
        // connect(this, &CircularBufferManagerWrapper::insertSignal, carData, &VehicleParser::replayStart);
        connect(timer, &QTimer::timeout, this, &CircularBufferManagerWrapper::increment);
        connect(timerIcons, &QTimer::timeout, this, &CircularBufferManagerWrapper::geartime);
    }

    double speed() const{
        return m_speed;
    }

    double rpm() const{
        return m_rpm;
    }
    
    double fuel() const{
        return m_fuel;
    }

    double temp() const{
        return m_temp;
    }

    double coolanttemp() const{
        return m_coolanttemp;
    }

    double clock() const{
        return m_clock;
    }

    double enginetemp() const{
        return m_enginetemp;
    }

    double oiltemp() const{
        return m_oiltemp;
    }

    double gearshift() const{
        return m_gearshift;
    }

    double seatbelt() const{
        return m_seatbelt;
    }

    double highlights() const{
        return m_highlights;
    }

    double abs() const{
        return m_abs;
    }

    double enginecheck() const{
        return m_enginecheck;
    }

    double parking() const{
        return m_parking;
    }

    void setSpeed(double newSpeed) {
        if (newSpeed != m_speed) {
            m_speed = newSpeed;
            emit speedChanged();
        }
    };

    void setRPM(double newRPM) {
        if (newRPM != m_rpm) {
            m_rpm = newRPM;
            emit rpmChanged();
        }
    };

    void setFuel(double newFuel) {
        if (newFuel != m_fuel) {
            m_fuel = newFuel;
            emit fuelChanged();
        }
    };

    void setTemp(double newTemp) {
        if (newTemp != m_temp) {
            m_temp = newTemp;
            emit tempChanged();
        }
    };

    void setCoolanttemp(double newCoolanttemp) {
        if (newCoolanttemp != m_coolanttemp) {
            m_coolanttemp = newCoolanttemp;
            emit coolanttempChanged();
        }
    };

    void setClock(double newClock) {
        if (newClock != m_clock) {
            m_clock = newClock;
            emit clockChanged();
        }
    };

    void setEnginetemp(double newEnginetemp) {
        if (newEnginetemp != m_enginetemp) {
            m_enginetemp = newEnginetemp;
            emit enginetempChanged();
        }
    };

    void setOilTemp(double newOilTemp) {
        if (newOilTemp != m_speed) {
            m_speed = newOilTemp;
            emit oilTempChanged();
        }
    };

    void setGearShift(double newGearShift) {
        if (newGearShift != m_gearshift) {
            m_gearshift = newGearShift;
            emit gearshiftChanged();
        }
    };

    void setSeatBelt(bool newSeatBelt) {
        if (m_seatbelt != newSeatBelt) {
            m_seatbelt = newSeatBelt;
            emit seatbeltChanged();
        }
    };

    void setHighlights(bool newHighlights) {
        if (m_highlights != newHighlights) {
            m_highlights = newHighlights;
            emit highlightsChanged();
        }
    };

    void setABS(bool newABS) {
        if (m_abs != newABS) {
            m_abs = newABS;
            emit absChanged();
        }
    };

    void setEngineCheck(bool newEngineCheck) {
        if (m_enginecheck != newEngineCheck) {
            m_enginecheck = newEngineCheck;
            emit enginecheckChanged();
        }
    };

    void setParking(bool newParking) {
        if (m_parking != newParking) {
            m_parking = newParking;
            emit parkingChanged();
        }
    };

    Q_INVOKABLE void togglePaused() {
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

signals:
    void speedChanged();
    void rpmChanged();
    void fuelChanged();
    void tempChanged();
    void coolanttempChanged();
    void clockChanged();
    void enginetempChanged();
    void oilTempChanged();

    void gearshiftChanged();

    void seatbeltChanged();
    void highlightsChanged();
    void absChanged();
    void enginecheckChanged();
    void parkingChanged();

    void togglePausedChanged(bool paused);

private slots:
    void increment() {
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

    void geartime() {
        if (m_gearshift >= 7) {
            m_gearshift = 0;
        } else {
        m_gearshift++;
        }
        emit gearshiftChanged();
    }

    void dataReady(int buffNum, double value) {
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
            break;
        case 5:
            setOilTemp(value);
            break;
        case 6:
            setGearShift(value);
            break;
        case 7:
            break;
        case 8:
            break;
        }
    }

private:
    double m_speed;
    double m_rpm;
    double m_fuel;
    double m_temp;
    double m_coolanttemp;
    double m_clock;
    double m_enginetemp;
    double m_oiltemp;

    double m_gearshift;

    bool m_seatbelt;
    bool m_highlights;
    bool m_abs;
    bool m_enginecheck;
    bool m_parking;

    QTimer *timer;
    QTimer *timerIcons;
};

#endif // CIRCULARBUFFERMANAGERWRAPPER_H
