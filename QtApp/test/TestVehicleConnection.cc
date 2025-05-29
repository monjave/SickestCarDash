#include <QtTest/QtTest>
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

    QTRY_VERIFY_WITH_TIMEOUT(initSpy.count() == 1, 6000);

    QVERIFY(receivedHex.size() >= 5);
}

void TestVehicleConnection::testHandlesEmptySerialPort() {
     QSignalSpy errorSpy(vc, &VehicleConnection::errorOccurred);

     vc->sendCommand("010C");

     QTest::qWait(100);

     QVERIFY(receivedHex.isEmpty());
     QVERIFY(errorSpy.isEmpty());
}

QTEST_MAIN(TestVehicleConnection)
#include "TestVehicleConnection.moc"