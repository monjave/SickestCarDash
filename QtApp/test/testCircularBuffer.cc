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

TEST(CircularBufferTest, Edge_Cases) {
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

    buf.pop();
    buf.pop();
    val = buf.pop();
    EXPECT_TRUE(buf.isEmpty());
    EXPECT_EQ(*val, 2);
}