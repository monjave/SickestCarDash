#include "gtest/gtest.h"
#include "CircularBufferManager.h"

TEST(TestCircularBufferManager, buffersCreatedAndSize) {
    CircularBufferManager buffMan = CircularBufferManager<int>(1024);
    ASSERT_EQ(buffMan.getBufferCount(), 1024);
    ASSERT_EQ(buffMan.getByteSize(), 4194304);
}

TEST(TestCircularBufferManager, initBuffer) {
    CircularBufferManager buffMan = CircularBufferManager<int>(1);
    // ASSERT_EQ(buffMan.accessBuffer(0, 1023), 0);
}


TEST(TestCircularBufferManager, Publish) {
    CircularBufferManager buffMan = CircularBufferManager<int>(2);

    std::vector<int> input = {1, 2};
    buffMan.publish(input);

    EXPECT_EQ(buffMan.peekBuffer(0), 1);
    EXPECT_EQ(buffMan.peekBuffer(1), 2);
}