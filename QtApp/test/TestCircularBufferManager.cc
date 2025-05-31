#include <QtTest/QtTest>
#include "CircularBufferManager.h"

class CircularBufferManagerTest : public QObject {
    Q_OBJECT

private slots:
    void InitBuffersAndSizeCheck();
    void Publish();
    void DoubleParamPublish();
    void DoubleParamPublishInvalidInput();
    void PublishInputTooLong();
    void ImproperAccessBuffer();
    void ImproperPeekBuffer();
    void ProperAccessBuffer();
    // void ConsumeAll();
};

void CircularBufferManagerTest::InitBuffersAndSizeCheck() {
    CircularBufferManager buffMan(1024);
    QCOMPARE(buffMan.getBufferCount(), 1024);
    QCOMPARE(buffMan.getByteSize(), 1024 * 1024 * sizeof(double)); // 4 194 304
    QCOMPARE(buffMan.accessBuffer(0).getCapacity(), 1024);
    QCOMPARE(buffMan.accessBuffer(1023).getCapacity(), 1024);
}

void CircularBufferManagerTest::Publish() {
    CircularBufferManager buffMan(5);
    std::vector<double> input = {1, 2, 3, 4, 5};
    buffMan.publish(input);

    QCOMPARE(buffMan.peekBuffer(0), 1);
    QCOMPARE(buffMan.peekBuffer(1), 2);
    QCOMPARE(buffMan.peekBuffer(2), 3);
    QCOMPARE(buffMan.peekBuffer(3), 4);
    QCOMPARE(buffMan.peekBuffer(4), 5);
}

void CircularBufferManagerTest::DoubleParamPublish() {
    CircularBufferManager buffMan(5);
    for (int i = 0; i < 5; ++i) {
        QCOMPARE(buffMan.publish(i + 1, i), 0);
    }
    QCOMPARE(buffMan.peekBuffer(0), 1);
    QCOMPARE(buffMan.peekBuffer(1), 2);
    QCOMPARE(buffMan.peekBuffer(2), 3);
    QCOMPARE(buffMan.peekBuffer(3), 4);
    QCOMPARE(buffMan.peekBuffer(4), 5);
}

void CircularBufferManagerTest::DoubleParamPublishInvalidInput() {
    CircularBufferManager buffMan(5);
    QCOMPARE(buffMan.publish(69, -420), 1);
    QCOMPARE(buffMan.publish(-420, 69), 1);
}

void CircularBufferManagerTest::PublishInputTooLong() {
    CircularBufferManager buffMan(4);
    std::vector<double> input = {1, 2, 3, 4, 5};
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, buffMan.publish(input));
}

void CircularBufferManagerTest::ImproperAccessBuffer() {
    CircularBufferManager buffMan(5);
    QVERIFY_THROWS_EXCEPTION(std::out_of_range, buffMan.accessBuffer(69));
    QVERIFY_THROWS_EXCEPTION(std::out_of_range, buffMan.accessBuffer(5));
    QVERIFY_THROWS_EXCEPTION(std::out_of_range, buffMan.accessBuffer(-1));
}

void CircularBufferManagerTest::ImproperPeekBuffer() {
    CircularBufferManager buffMan(5);
    QVERIFY_THROWS_EXCEPTION(std::out_of_range, buffMan.peekBuffer(69));
    QVERIFY_THROWS_EXCEPTION(std::out_of_range, buffMan.peekBuffer(5));
    QVERIFY_THROWS_EXCEPTION(std::out_of_range, buffMan.peekBuffer(-1));
}

void CircularBufferManagerTest::ProperAccessBuffer() {
    CircularBufferManager buffMan(5);
    QCOMPARE(buffMan.accessBuffer(0).getSize(), 0);
    QCOMPARE(buffMan.accessBuffer(0).getCapacity(), 1024);
    QCOMPARE(buffMan.accessBuffer(1).getSize(), 0);
    QCOMPARE(buffMan.accessBuffer(1).getCapacity(), 1024);
}

// void CircularBufferManagerTest::ConsumeAll() {
//     CircularBufferManager buffMan(5);
//     buffMan.accessBuffer(0).push(0);
//     buffMan.accessBuffer(1).push(1);
//     buffMan.accessBuffer(2).push(2);
//     buffMan.accessBuffer(3).push(3);
//     buffMan.accessBuffer(4).push(4);

//     std::vector<int> expected = {0,1,2,3,4};
//     QCOMPARE(buffMan.consumeAll(), expected);
// }

QTEST_MAIN(CircularBufferManagerTest)
#include "TestCircularBufferManager.moc"
