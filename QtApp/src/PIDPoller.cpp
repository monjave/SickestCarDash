#include "PIDPoller.h"
#include <QThread>
#include <QtConcurrent>

PIDPoller::PIDPoller(QObject *parent)
    : QObject(parent), running(0) {}

void PIDPoller::startPolling() {
    if (running.loadRelaxed()) {
        return;
    }

    running.storeRelaxed(1);
    QtConcurrent::run([this]() {
        while (running.loadAcquire()) {
            qDebug() << "PIDPoller calling run";
            emit requestPid("010D");  // Request Speed
            qDebug() << "Speed requested";
            QThread::msleep(200);  // Small delay to avoid flooding the bus
            emit requestPid("010C");  // Request RPM
            qDebug() << "RPM requested";
            QThread::msleep(200);
            emit requestPid("22F40D");  // Request Fuel Level
            qDebug() << "Fuel Level requested";
            QThread::msleep(200);
            emit requestPid("0105");  // Request Coolant Temp
            qDebug() << "Coolant Temp requested";
            QThread::msleep(200);
            //emit requestPid("0111"); Request Throttle Position, only needed for racing telemetry
            emit requestPid("015C");  // Request Oil Temp
            qDebug() << "Oil Temp requested";
            QThread::msleep(200);
            emit requestPid("01A4");  // Request Gear
            qDebug() << "Gear requested";
            QThread::msleep(200);
            emit requestPid("0142");  // Request Battery Voltage
            qDebug() << "Battery Voltage requested";
            QThread::msleep(200);
            emit requestPid("03");  // Request Stored DTCs
            qDebug() << "DTC requested";

            QThread::msleep(300);  
        }
    });
}

void PIDPoller::stopPolling() {
    running.storeRelaxed(0);
}

void PIDPoller::onInitComplete() {
     QTimer::singleShot(300, this, &PIDPoller::startPolling);
}
