#include <QtTest>
#include "VehicleConnection.h"
#include "MockQSerialPort.h"

/* ----------  Minimal mock for QSerialPort  ---------------- */

class MockSerialPort : public QSerialPort
{
    Q_OBJECT
public:
    explicit MockSerialPort(QObject *parent = nullptr)
        : QSerialPort(parent), m_isOpen(false) {}

    bool open(OpenMode mode) override
    {
        Q_UNUSED(mode)
        m_isOpen = true;
        return true;               // always succeed
    }

    bool isOpen() const override  { return m_isOpen; }

    qint64 write(const QByteArray &data) override
    {
        m_written.append(data);
        return data.size();
    }

    QByteArray readAll() override
    {
        QByteArray tmp = m_readBuffer;
        m_readBuffer.clear();
        return tmp;
    }

    /* helpers for the test fixture */
    const QByteArray &written() const { return m_written; }
    void clearWritten()               { m_written.clear(); }

    void injectIncoming(const QByteArray &data)
    {
        m_readBuffer.append(data);
        emit readyRead();           // pretend HW has data
    }

private:
    bool        m_isOpen;
    QByteArray  m_written;
    QByteArray  m_readBuffer;
};

/* ----------  Fixture under test  --------------------------- */

class VehicleConnectionTest : public QObject
{
    Q_OBJECT

private slots:
<<<<<<< HEAD
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
=======
    void init();          ///< executed before *each* test
    void cleanup();       ///< executed after  *each* test

    void sendCommand_appendsCR();
    void beginInitSequence_sendsAllInitCommands();
    void handleReadyRead_emitsHexSignal();

private:
    MockSerialPort      *mockPort {};
    VehicleConnection   *uut      {};   ///< “unit under test”
};

/* ----------  Test‑case boiler‑plate  ----------------------- */

void VehicleConnectionTest::init()
{
    /* Replace the real serial port with our mock:
       We can do this because VehicleConnection creates the port in
       its constructor, but we have access to the pointer via QObject
       hierarchy: it’s the only QSerialPort child.                    */
    uut = new VehicleConnection;          // uses default ctor
    mockPort = new MockSerialPort(uut);   // same parent

    /* Swap pointers */
    delete uut->findChild<QSerialPort *>();      // throw away real port
    const_cast<QSerialPort *&>(uut->serial) = mockPort; // hack‑in mock

    mockPort->open(QIODevice::ReadWrite);        // mark open
}

void VehicleConnectionTest::cleanup()
{
    delete uut;
    uut = nullptr;
    mockPort = nullptr;
}

/* ----------  INDIVIDUAL TESTS  ----------------------------- */

void VehicleConnectionTest::sendCommand_appendsCR()
{
    uut->sendCommand("010D");
    QCOMPARE(mockPort->written(), QByteArray("010D\r"));
>>>>>>> 80e27dc (Merged Dom's code and fixed merge conflicts)
}

void VehicleConnectionTest::initTest() {

}





QTEST_MAIN(VehicleConnectionTest)
#include "TestVehicleConnection.moc"
