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