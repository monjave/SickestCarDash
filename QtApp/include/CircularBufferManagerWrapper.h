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

    Q_PROPERTY(bool paused READ paused WRITE setPaused NOTIFY togglePausedChanged)

public:
    explicit CircularBufferManagerWrapper(QObject *parent = nullptr) : QObject(parent), m_speed(0),
        m_rpm(0), m_fuel(0), m_temp(100), m_coolanttemp(0), m_clock(0), m_enginetemp(0), m_oiltemp(0), m_gearshift(0), m_ispaused(true) {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &CircularBufferManagerWrapper::increment);
        //timer->start(1500);


    }

    /*Q_INVOKABLE void toggleTimer() {
        if (m_ispaused) {
            timer->stop();
        } else {
            timer->start(1500);
        }
    }; */
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

    Q_INVOKABLE void togglePaused() {
        if (timer->isActive()) {
            timer->stop();
        } else {
        timer->start(1500);
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

        emit speedChanged();
        emit rpmChanged();
        emit fuelChanged();
        emit tempChanged();
        emit oilTempChanged();
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

    QTimer *timer;

    bool m_ispaused;
};

#endif // CIRCULARBUFFERMANAGERWRAPPER_H
