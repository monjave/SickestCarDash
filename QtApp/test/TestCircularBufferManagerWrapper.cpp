#include <QtTest>
#include "CircularBufferManagerWrapper.h"

class CircularBufferManagerWrapperTest : public QObject {
    Q_OBJECT

private slots:
    void constructorTest();
    void sendCommandPass();
    void sendCommandFail();
    void ReadyReadPass();
    void ReadyReadFail();

};

void CircularBufferManagerWrapperTest::constructorTest() {
    
}

void CircularBufferManagerWrapperTest::sendCommandPass() {

}

void CircularBufferManagerWrapperTest::sendCommandFail() {

}

void CircularBufferManagerWrapperTest::ReadyReadPass() {

}

void CircularBufferManagerWrapperTest::ReadyReadFail() {

}

QTEST_MAIN(CircularBufferManagerWrapperTest)
#include "TestCircularBufferManagerWrapper.moc"
