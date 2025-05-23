// #include "QtTest/QtTest"
// #include "VehicleConnection.h"

// class VehicleConnectionTest : public QObject {
//     Q_OBJECT

// private slots:

// }

// TestVehicleConnection.cc
#include <QtTest>
#include "VehicleConnection.h"

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
}

void VehicleConnectionTest::beginInitSequence_sendsAllInitCommands()
{
    /* Capture commands via MockSerialPort and advance the timer
       manually with a QTest event‑loop wait.                     */
    QSignalSpy initSpy(uut, &VehicleConnection::initComplete);

    uut->beginInitSequence();

    /* wait up to (commands * 1 s) + margin                        */
    const int sequenceTimeMs = 1000 * 5 + 200;
    QVERIFY(initSpy.wait(sequenceTimeMs));

    const QList<QByteArray> expected =
        {"ATZ\r", "ATE0\r", "ATL0\r", "ATS0\r", "ATSP2\r"};

    /* The mock accumulates writes in chronological order          */
    QByteArray all = mockPort->written();
    QList<QByteArray> chunks = all.split('\r');
    chunks.removeLast();            // final split is empty after trailing \r

    QCOMPARE(chunks, expected);
}

void VehicleConnectionTest::handleReadyRead_emitsHexSignal()
{
    QSignalSpy spy(uut, &VehicleConnection::rawHexReceived);

    /* “41 0C 1A F8\r”  == typical RPM reply 0x1AF8                */
    mockPort->injectIncoming(QByteArray::fromHex("410C1AF8") + "\r");

    QVERIFY(spy.wait(50));          // allow event loop to spin

    QCOMPARE(spy.count(), 1);
    const QString payload = spy.takeFirst().at(0).toString();
    QCOMPARE(payload, QString("41 0C 1A F8"));
}

/* ----------  main() wrapper  -------------------------------- */
QTEST_MAIN(VehicleConnectionTest)
#include "TestVehicleConnection.moc"
