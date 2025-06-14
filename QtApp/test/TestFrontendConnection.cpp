#include <QtTest>
#include "FrontendConnection.h"

class TestFrontendConnection : public QObject {
    Q_OBJECT

private slots:
    void qPropertyTest();
    void engineTest();
};

void TestFrontendConnection::qPropertyTest() {
    CircularBufferManagerWrapper* properties = new CircularBufferManagerWrapper();
    properties->setSpeed(15.5);
    QCOMPARE(properties->speed(), 15.5);

    QSignalSpy spy(properties, &CircularBufferManagerWrapper::speedChanged);

    properties->setSpeed(25.1);
    properties->setSpeed(28.9);
    QCOMPARE(spy.count(), 2);
}

void TestFrontendConnection::engineTest() {

}

QTEST_MAIN(TestFrontendConnection)
#include "TestFrontendConnection.moc"
