#include <QtTest>
#include "CircularBufferManagerWrapper.h"

class CircularBufferManagerWrapperTest : public QObject {
    Q_OBJECT

private slots:
    void qPropertyTest();
};

void CircularBufferManagerWrapperTest::qPropertyTest() {
    CircularBufferManagerWrapper* properties = new CircularBufferManagerWrapper();
    properties->setSpeed(15.5);
    QCOMPARE(properties->speed(), 15.5);

    QSignalSpy spy(properties, &CircularBufferManagerWrapper::speedChanged);

    properties->setSpeed(25.1);
    properties->setSpeed(28.9);
    QCOMPARE(spy.count(), 2);
}

QTEST_MAIN(CircularBufferManagerWrapperTest)
#include "TestCircularBufferManagerWrapper.moc"
