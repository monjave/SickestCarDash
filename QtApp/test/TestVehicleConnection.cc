#include <QtTest>
#include "VehicleConnection.h"
#include "MockQSerialPort.h"

class TestVehicleConnection : public QObject {
    Q_OBJECT

private slots:
    void init();
    void testInitializationSequence();
    void testHandlesEmptySerialPort();

private:
    MockQSerialPort *mockPort;
    VehicleConnection *vc;
    QStringList receivedHex;
};


void TestVehicleConnection::init() {
    mockPort = new MockQSerialPort(this);
    vc = new VehicleConnection(mockPort);

    connect(vc, &VehicleConnection::rawHexReceived, this, [&](const QString &hex) {
        receivedHex.append(hex);
    });
}

void TestVehicleConnection::testInitializationSequence() {
    mockPort->setResponse({"ELM327", "OK", "OK", "OK", "OK"});

    QSignalSpy initSpy(vc, &VehicleConnection::initComplete);
    
    vc->beginInitSequence();

    QTRY_VERIFY_WITH_TIMEOUT(initSpy.count() == 1, 7000);

    QVERIFY(receivedHex.size() >= 5);
}

void VehicleConnectionTest::ReadyReadPass() {

}





QTEST_MAIN(VehicleConnectionTest)
#include "TestVehicleConnection.moc"
