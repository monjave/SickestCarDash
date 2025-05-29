#include <QtTest>
#include "VehicleConnection.h"
#include "MockQSerialPort.h"

class VehicleConnectionTest : public QObject {
    Q_OBJECT

private slots:
    void constructorTest();
    void sendCommandPass();
    void sendCommandFail();
    void ReadyReadPass();
    void ReadyReadFail();

};

void VehicleConnectionTest::constructorTest() {
    
}

void VehicleConnectionTest::sendCommandPass() {

}

void VehicleConnectionTest::sendCommandFail() {

}

void VehicleConnectionTest::ReadyReadPass() {

}

void VehicleConnectionTest::ReadyReadFail() {

}

QTEST_MAIN(VehicleConnectionTest)
#include "TestVehicleConnection.moc"