#ifndef CIRCULARBUFFERMANAGERWRAPPER_H
#define CIRCULARBUFFERMANAGERWRAPPER_H

#include <QObject>
#include "CircularBufferManager.h"

class CircularBufferManagerWrapper : public QObject {
    Q_OBJECT
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    /*Q_PROPERTY(int rpm READ rpm WRITE setRPM NOTIFY rpmChanged)
    Q_PROPERTY(int fuel READ fuel WRITE setFuel NOTIFY fuelChanged)
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged) */

public:
    explicit CircularBufferManagerWrapper(QObject *parent = nullptr) : QObject(parent), m_speed(100),
    m_rpm(0), m_fuel(0), m_temp(0), m_coolanttemp(0), m_clock(0), m_enginetemp(0) {}
    //CircularBufferManager<int> manager;
    //std::vector<int> data = manager.consumeAll();
    //std::vector<int> data = {speedVal};

    int speed() const{
        return m_speed;
    }

    /*int speed() const{
        return m_speed;
    }

    int speed() const{
        return m_speed;
    }

    int speed() const{
        return m_speed;
    }

    int speed() const{
        return m_speed;
    }

    int speed() const{
        return m_speed;
    }

    int speed() const{
        return m_speed;
    }

    int speed() const{
        return m_speed;
    }

    int speed() const{
        return m_speed;
    }*/

    void setSpeed(int newSpeed) {
        if (newSpeed != m_speed) {
            m_speed = newSpeed;
            emit speedChanged();
        }
    };

    /*void setSpeed(int newSpeed) {
        if (newSpeed != m_speed) {
            m_speed = newSpeed;
            emit speedChanged();
        }
    };

    void setSpeed(int newSpeed) {
        if (newSpeed != m_speed) {
            m_speed = newSpeed;
            emit speedChanged();
        }
    };

    void setSpeed(int newSpeed) {
        if (newSpeed != m_speed) {
            m_speed = newSpeed;
            emit speedChanged();
        }
    };

    void setSpeed(int newSpeed) {
        if (newSpeed != m_speed) {
            m_speed = newSpeed;
            emit speedChanged();
        }
    };

    void setSpeed(int newSpeed) {
        if (newSpeed != m_speed) {
            m_speed = newSpeed;
            emit speedChanged();
        }
    };

    void setSpeed(int newSpeed) {
        if (newSpeed != m_speed) {
            m_speed = newSpeed;
            emit speedChanged();
        }
    };

    void setSpeed(int newSpeed) {
        if (newSpeed != m_speed) {
            m_speed = newSpeed;
            emit speedChanged();
        }
    };

    void setSpeed(int newSpeed) {
        if (newSpeed != m_speed) {
            m_speed = newSpeed;
            emit speedChanged();
        }
    }; */

signals:
    void speedChanged();
    /*void speedChanged();
    void speedChanged();
    void speedChanged();
    void speedChanged();
    void speedChanged();
    void speedChanged();
    void speedChanged();
    void speedChanged(); */

private:
    int m_speed;
    int m_rpm;
    int m_fuel;
    int m_temp;
    int m_coolanttemp;
    int m_clock;
    int m_enginetemp;
    //int m_speed;
    //int m_speed;
};

#endif // CIRCULARBUFFERMANAGERWRAPPER_H
