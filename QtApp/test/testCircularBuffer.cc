#include "gtest/gtest.h"
#include "CircularBuffer.h"

TEST(CircularBufferTest, PushAndPop) {
    CircularBuffer<int> buf(3);

    EXPECT_TRUE(buf.isEmpty());

    buf.push(1);
    buf.push(2);
    buf.push(3);

    EXPECT_TRUE(buf.isFull());

    auto val = buf.pop();
    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(*val, 3); 

    auto peek = buf.peek();
    ASSERT_TRUE(peek.has_value());
    EXPECT_EQ(*peek, 2);
}

TEST(CircularBufferTest, Simple) {
    CircularBuffer<int> buf(3);

    EXPECT_TRUE(buf.isEmpty());

    ASSERT_TRUE(buf.pop() == std::nullopt);

    buf.push(1);
    buf.push(2);
    buf.push(3);
    buf.push(4);

    buf.printBuffer();

    auto val = buf.peek();
    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(*val, 4);

    int size = buf.getSize();
    EXPECT_EQ(size, 3);

    buf.pop();
    buf.pop();
    val = buf.pop();
    size = buf.getSize();
    EXPECT_TRUE(buf.isEmpty());
    EXPECT_EQ(*val, 2);
    EXPECT_EQ(size, 0);
}

TEST(CircularBufferTest, PushPopBasic) {
    CircularBuffer<int> buf(3);
    EXPECT_TRUE(buf.isEmpty());
    EXPECT_FALSE(buf.isFull());
    EXPECT_EQ(buf.getSize(), 0);

    EXPECT_EQ(buf.push(10), 0);
    EXPECT_EQ(buf.push(20), 0);
    EXPECT_EQ(buf.push(30), 0);

    EXPECT_FALSE(buf.isEmpty());
    EXPECT_TRUE(buf.isFull());
    EXPECT_EQ(buf.getSize(), 3);
    EXPECT_EQ(buf.getCapacity(), 3);

    auto v1 = buf.pop();
    ASSERT_TRUE(v1.has_value());
    EXPECT_EQ(*v1, 30);

    auto v2 = buf.pop();
    ASSERT_TRUE(v2.has_value());
    EXPECT_EQ(*v2, 20);

    auto v3 = buf.pop();
    ASSERT_TRUE(v3.has_value());
    EXPECT_EQ(*v3, 10);

    EXPECT_TRUE(buf.isEmpty());
    EXPECT_EQ(buf.getSize(), 0);
}

TEST(CircularBufferTest, SingleOverwrite) {
    CircularBuffer<int> buf(3);
    buf.push(1);
    buf.push(2);
    buf.push(3);
    EXPECT_TRUE(buf.isFull());

    EXPECT_EQ(buf.push(4), 1);
    EXPECT_TRUE(buf.isFull());
    EXPECT_EQ(buf.getSize(), 3);

    EXPECT_EQ(*buf.pop(), 4);
    EXPECT_EQ(*buf.pop(), 3);
    EXPECT_EQ(*buf.pop(), 2);
    EXPECT_TRUE(buf.isEmpty());
}

TEST(CircularBufferTest, MultipleOverwrites) {
    CircularBuffer<int> buf(3);
    for (int i = 1; i <= 5; ++i) {
        int8_t ret = buf.push(i);
        if (i <= 3) EXPECT_EQ(ret, 0);
        else          EXPECT_EQ(ret, 1);
    }
    EXPECT_TRUE(buf.isFull());
    EXPECT_EQ(buf.getSize(), 3);

    EXPECT_EQ(*buf.pop(), 5);
    EXPECT_EQ(*buf.pop(), 4);
    EXPECT_EQ(*buf.pop(), 3);
    EXPECT_TRUE(buf.isEmpty());
}

TEST(CircularBufferTest, InterleavedWrapAndOverwrite) {
    CircularBuffer<int> buf(3);
    buf.push(100);
    buf.push(200);
    buf.push(300);
    EXPECT_EQ(*buf.pop(), 300);
    EXPECT_EQ(buf.getSize(), 2);

    EXPECT_EQ(buf.push(400), 0);
    EXPECT_EQ(buf.push(500), 1);

    EXPECT_EQ(buf.getSize(), 3);
    EXPECT_EQ(*buf.pop(), 500);
    EXPECT_EQ(*buf.pop(), 400);
    EXPECT_EQ(*buf.pop(), 200);
    EXPECT_TRUE(buf.isEmpty());
}

TEST(CircularBufferTest, PeekNonDestructive) {
    CircularBuffer<std::string> buf(2);
    buf.push("first");
    buf.push("second");

    EXPECT_EQ(buf.getSize(), 2);
    auto p1 = buf.peek();
    ASSERT_TRUE(p1.has_value());
    EXPECT_EQ(*p1, "second");
    EXPECT_EQ(buf.getSize(), 2);

    auto p2 = buf.peek();
    ASSERT_TRUE(p2.has_value());
    EXPECT_EQ(*p2, "second");
    EXPECT_EQ(buf.getSize(), 2);
}

TEST(CircularBufferTest, PushReturnCodes) {
    CircularBuffer<int> buf(2);
    EXPECT_EQ(buf.push(9),  0);
    EXPECT_EQ(buf.push(8),  0);
    EXPECT_EQ(buf.push(7),  1);
    EXPECT_EQ(buf.push(6),  1); 
}

TEST(CircularBufferTest, PopPeekEmpty) {
    CircularBuffer<int> buf(5);
    EXPECT_TRUE(buf.isEmpty());
    EXPECT_EQ(buf.pop(), std::nullopt);
    EXPECT_EQ(buf.peek(), std::nullopt);
    EXPECT_EQ(buf.getSize(), 0);
}