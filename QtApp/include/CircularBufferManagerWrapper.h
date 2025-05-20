#ifndef CIRCULARBUFFERMANAGERWRAPPER_H
#define CIRCULARBUFFERMANAGERWRAPPER_H

#include <QObject>
#include <QTimer>
#include "CircularBufferManager.h"

class CircularBufferManagerWrapper : public QObject {
    Q_OBJECT
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(int rpm READ rpm WRITE setRPM NOTIFY rpmChanged)
    Q_PROPERTY(int fuel READ fuel WRITE setFuel NOTIFY fuelChanged)
    Q_PROPERTY(int temp READ temp WRITE setTemp NOTIFY tempChanged)
    Q_PROPERTY(int coolanttemp READ coolanttemp WRITE setCoolanttemp NOTIFY coolanttempChanged)
    Q_PROPERTY(int clock READ clock WRITE setClock NOTIFY clockChanged)
    Q_PROPERTY(int enginetemp READ enginetemp WRITE setEnginetemp NOTIFY enginetempChanged)
    Q_PROPERTY(int oiltemp READ oiltemp WRITE setOilTemp NOTIFY oilTempChanged)

    Q_PROPERTY(int gearshift READ gearshift WRITE setGearShift NOTIFY gearshiftChanged)

    Q_PROPERTY(bool seatbelt READ seatbelt WRITE setSeatBelt NOTIFY seatbeltChanged)
    Q_PROPERTY(bool highlights READ highlights WRITE setHighlights NOTIFY highlightsChanged)
    Q_PROPERTY(bool abs READ abs WRITE setABS NOTIFY absChanged)
    Q_PROPERTY(bool enginecheck READ enginecheck WRITE setEngineCheck NOTIFY enginecheckChanged)
    Q_PROPERTY(bool parking READ parking WRITE setParking NOTIFY parkingChanged)

    Q_PROPERTY(bool paused READ paused WRITE setPaused NOTIFY togglePausedChanged)

public:
    explicit CircularBufferManagerWrapper(QObject *parent = nullptr) : QObject(parent), m_speed(160),
    m_rpm(75), m_fuel(0), m_temp(0), m_coolanttemp(0), m_clock(0), m_enginetemp(0) {}
    //CircularBufferManager<int> manager;
    //std::vector<int> data = manager.consumeAll();
    //std::vector<int> data = {speedVal};

    bool paused() const {
        return m_ispaused;
    }

    int speed() const{
        return m_speed;
    }

    int rpm() const{
        return m_rpm;
    }

    int fuel() const{
        return m_fuel;
    }

    int temp() const{
        return m_temp;
    }

    int coolanttemp() const{
        return m_coolanttemp;
    }

    int clock() const{
        return m_clock;
    }

    int enginetemp() const{
        return m_enginetemp;
    }

    int oiltemp() const{
        return m_oiltemp;
    }

    int gearshift() const{
        return m_gearshift;
    }

    int seatbelt() const{
        return m_seatbelt;
    }

    int highlights() const{
        return m_highlights;
    }

    int abs() const{
        return m_abs;
    }

    int enginecheck() const{
        return m_enginecheck;
    }

    int parking() const{
        return m_parking;
    }

    void setPaused(bool paused) {
        if (m_ispaused == paused) return;
        m_ispaused = paused;
        emit togglePausedChanged(m_ispaused);
        if (m_ispaused)
            timer->stop();
        else
            timer->start(1500);
    }

    void setSpeed(int newSpeed) {
        if (newSpeed != m_speed) {
            m_speed = newSpeed;
            emit speedChanged();
        }
    };

    void setRPM(int newRPM) {
        if (newRPM != m_rpm) {
            m_rpm = newRPM;
            emit rpmChanged();
        }
    };

    void setFuel(int newFuel) {
        if (newFuel != m_fuel) {
            m_fuel = newFuel;
            emit fuelChanged();
        }
    };

    void setTemp(int newTemp) {
        if (newTemp != m_temp) {
            m_temp = newTemp;
            emit tempChanged();
        }
    };

    void setCoolanttemp(int newCoolanttemp) {
        if (newCoolanttemp != m_coolanttemp) {
            m_coolanttemp = newCoolanttemp;
            emit coolanttempChanged();
        }
    };

    void setClock(int newClock) {
        if (newClock != m_clock) {
            m_clock = newClock;
            emit clockChanged();
        }
    };

    void setEnginetemp(int newEnginetemp) {
        if (newEnginetemp != m_enginetemp) {
            m_enginetemp = newEnginetemp;
            emit enginetempChanged();
        }
    };

    void setOilTemp(int newOilTemp) {
        if (newOilTemp != m_speed) {
            m_speed = newOilTemp;
            emit oilTempChanged();
        }
    };

    void setGearShift(int newGearShift) {
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

    /*void pause() {
        if (m_ispaused) {
            timer->stop();
        } else {
            timer->start(1500);
        }
    } */



private:
    int m_speed;
    int m_rpm;
    int m_fuel;
    int m_temp;
    int m_coolanttemp;
    int m_clock;
    int m_enginetemp;
    int m_oiltemp;

    int m_gearshift;

    bool m_seatbelt;
    bool m_highlights;
    bool m_abs;
    bool m_enginecheck;
    bool m_parking;

    QTimer *timer;
    QTimer *timerIcons;

    bool m_ispaused;
};

#endif // CIRCULARBUFFERMANAGERWRAPPER_H
