#include <QtTest>
#include "VehicleConnection.h"
#include "MockQSerialPort.h"

class VehicleConnectionTest : public QObject {
    Q_OBJECT

private slots:
    // Declare test functions here
    void initTest();
};

void VehicleConnectionTest::initTest() {

}





QTEST_MAIN(VehicleConnectionTest)
#include "TestVehicleConnection.moc"
