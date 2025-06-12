#include "PIDPoller.h"
#include <QThread>
#include <QtConcurrent>

PIDPoller::PIDPoller(QObject *parent)
    : QObject(parent), running(0) {}

void PIDPoller::startPolling() {
    if (running.loadRelaxed()) {
        return;
    }

    running.storeRelaaxed(1);
    QtConcurrent::run([this]() {
        while (running.loadAcquire()) {
            emit requestPid("010D");  // Request Speed
            QThread::msleep(100);  // Small delay to avoid flooding the bus
            emit requestPid("010C");  // Request RPM
            QThread::msleep(100);
            emit requestPid("012F");  // Request Fuel Level
            QThread::msleep(100);
            emit requestPid("0105");  // Request Coolant Temp
            QThread::msleep(100);
            //emit requestPid("0111"); Request Throttle Position, only needed for racing telemetry
            emit requestPid("015C");  // Request Oil Temp
            QThread::msleep(100);
            emit requestPid("01A4");  // Request Gear
            QThread::msleep(100);
            emit requestPid("0142");  // Request Battery Voltage
            QThread::msleep(100);
            emit requestPid("03");  // Request Stored DTCs

            QThread::msleep(300);  
        }
    });
}

void PIDPoller::stopPolling() {
    running.storeRelaxed(0);
}
