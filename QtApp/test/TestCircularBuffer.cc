#include <QtTest/QtTest>
#include "CircularBuffer.h"

class CircularBufferTest : public QObject {
    Q_OBJECT

private slots:
    void PushAndPop();
    void Simple();
    void PushPopBasic();
    void SingleOverwrite();
    void MultipleOverwrites();
    void InterleavedWrapAndOverwrite();
    void PeekNonDestructive();
    void PushReturnCodes();
    void PopPeekEmpty();
};

void CircularBufferTest::PushAndPop() {
    CircularBuffer<int> buf(3);
    QVERIFY(buf.isEmpty());

    buf.push(1);
    buf.push(2);
    buf.push(3);
    QVERIFY(buf.isFull());

    auto val = buf.pop();
    QVERIFY(val.has_value());
    QCOMPARE(*val, 3);

    auto peek = buf.peek();
    QVERIFY(peek.has_value());
    QCOMPARE(*peek, 2);
}

void CircularBufferTest::Simple() {
    CircularBuffer<int> buf(3);
    QVERIFY(buf.isEmpty());
    QVERIFY(buf.pop() == std::nullopt);

    buf.push(1);
    buf.push(2);
    buf.push(3);
    buf.push(4); // Overwrites

    buf.printBuffer();

    auto val = buf.peek();
    QVERIFY(val.has_value());
    QCOMPARE(*val, 4);

    int size = buf.getSize();
    QCOMPARE(size, 3);

    buf.pop();
    buf.pop();
    val = buf.pop();
    size = buf.getSize();

    QVERIFY(buf.isEmpty());
    QCOMPARE(*val, 2);
    QCOMPARE(size, 0);
}

void CircularBufferTest::PushPopBasic() {
    CircularBuffer<int> buf(3);
    QVERIFY(buf.isEmpty());
    QVERIFY(!buf.isFull());
    QCOMPARE(buf.getSize(), 0);

    QCOMPARE(buf.push(10), 0);
    QCOMPARE(buf.push(20), 0);
    QCOMPARE(buf.push(30), 0);

    QVERIFY(!buf.isEmpty());
    QVERIFY(buf.isFull());
    QCOMPARE(buf.getSize(), 3);
    QCOMPARE(buf.getCapacity(), 3);

    auto v1 = buf.pop();
    QVERIFY(v1.has_value());
    QCOMPARE(*v1, 30);

    auto v2 = buf.pop();
    QVERIFY(v2.has_value());
    QCOMPARE(*v2, 20);

    auto v3 = buf.pop();
    QVERIFY(v3.has_value());
    QCOMPARE(*v3, 10);

    QVERIFY(buf.isEmpty());
    QCOMPARE(buf.getSize(), 0);
}

void CircularBufferTest::SingleOverwrite() {
    CircularBuffer<int> buf(3);
    buf.push(1);
    buf.push(2);
    buf.push(3);
    QVERIFY(buf.isFull());

    QCOMPARE(buf.push(4), 1);
    QVERIFY(buf.isFull());
    QCOMPARE(buf.getSize(), 3);

    QCOMPARE(*buf.pop(), 4);
    QCOMPARE(*buf.pop(), 3);
    QCOMPARE(*buf.pop(), 2);
    QVERIFY(buf.isEmpty());
}

void CircularBufferTest::MultipleOverwrites() {
    CircularBuffer<int> buf(3);
    for (int i = 1; i <= 5; ++i) {
        int8_t ret = buf.push(i);
        if (i <= 3) QCOMPARE(ret, 0);
        else        QCOMPARE(ret, 1);
    }
    QVERIFY(buf.isFull());
    QCOMPARE(buf.getSize(), 3);

    QCOMPARE(*buf.pop(), 5);
    QCOMPARE(*buf.pop(), 4);
    QCOMPARE(*buf.pop(), 3);
    QVERIFY(buf.isEmpty());
}

void CircularBufferTest::InterleavedWrapAndOverwrite() {
    CircularBuffer<int> buf(3);
    buf.push(100);
    buf.push(200);
    buf.push(300);
    QCOMPARE(*buf.pop(), 300);
    QCOMPARE(buf.getSize(), 2);

    QCOMPARE(buf.push(400), 0);
    QCOMPARE(buf.push(500), 1);

    QCOMPARE(buf.getSize(), 3);
    QCOMPARE(*buf.pop(), 500);
    QCOMPARE(*buf.pop(), 400);
    QCOMPARE(*buf.pop(), 200);
    QVERIFY(buf.isEmpty());
}

void CircularBufferTest::PeekNonDestructive() {
    CircularBuffer<std::string> buf(2);
    buf.push("first");
    buf.push("second");

    QCOMPARE(buf.getSize(), 2);

    auto p1 = buf.peek();
    QVERIFY(p1.has_value());
    QCOMPARE(*p1, std::string("second"));
    QCOMPARE(buf.getSize(), 2);

    auto p2 = buf.peek();
    QVERIFY(p2.has_value());
    QCOMPARE(*p2, std::string("second"));
    QCOMPARE(buf.getSize(), 2);
}

void CircularBufferTest::PushReturnCodes() {
    CircularBuffer<int> buf(2);
    QCOMPARE(buf.push(9), 0);
    QCOMPARE(buf.push(8), 0);
    QCOMPARE(buf.push(7), 1);
    QCOMPARE(buf.push(6), 1);
}

void CircularBufferTest::PopPeekEmpty() {
    CircularBuffer<int> buf(5);
    QVERIFY(buf.isEmpty());
    QCOMPARE(buf.pop(), std::nullopt);
    QCOMPARE(buf.peek(), std::nullopt);
    QCOMPARE(buf.getSize(), 0);
}

QTEST_MAIN(CircularBufferTest)
#include "TestCircularBuffer.moc"