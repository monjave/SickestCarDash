#ifndef CIRCULARBUFFERMANAGERWRAPPER_H
#define CIRCULARBUFFERMANAGERWRAPPER_H

#include <QObject>
#include <QDir>
#include <QTimer>
#include "CircularBufferManager.h"
#include "VehicleParser.h"

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
    //Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)

public:
    explicit CircularBufferManagerWrapper(QObject *parent = nullptr) : QObject(parent), m_speed(0),
        m_rpm(0), m_fuel(0), m_temp(0), m_coolanttemp(0), m_clock(0), m_enginetemp(0), m_oiltemp(0) {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &CircularBufferManagerWrapper::increment);
        timer->start(1500);


    }
    //CircularBufferManager<int> manager;
    //std::vector<int> data = manager.consumeAll();
    //std::vector<int> data = {speedVal};

    int speed() const{
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

    /*int speed() const{
        return m_speed;
    }*/

    void setSpeed(int newSpeed) {
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

    /*void setSpeed(int newSpeed) {
        if (newSpeed != m_speed) {
            m_speed = newSpeed;
            emit speedChanged();
        }
    };*/

signals:
    void speedChanged();
    void rpmChanged();
    void fuelChanged();
    void tempChanged();
    void coolanttempChanged();
    void clockChanged();
    void enginetempChanged();
    void oilTempChanged();
    //void speedChanged();

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

private:
    int m_speed;
    int m_rpm;
    int m_fuel;
    int m_temp;
    int m_coolanttemp;
    int m_clock;
    int m_enginetemp;
    int m_oiltemp;
    //int m_speed;
};

#endif // CIRCULARBUFFERMANAGERWRAPPER_H
