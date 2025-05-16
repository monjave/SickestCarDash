#include "gtest/gtest.h"
#include "CircularBufferManager.h"

TEST(TestCircularBufferManager, InitBuffersAndSizeCheck) {
    CircularBufferManager buffMan = CircularBufferManager<int>(1024);
    ASSERT_EQ(buffMan.getBufferCount(), 1024);
    ASSERT_EQ(buffMan.getByteSize(), 4194304);
    ASSERT_EQ(buffMan.accessBuffer(0).getCapacity(), 1024);
    ASSERT_EQ(buffMan.accessBuffer(1023).getCapacity(), 1024);
}

TEST(TestCircularBufferManager, Publish) {
    CircularBufferManager buffMan = CircularBufferManager<int>(5);

    std::vector<int> input = {1, 2, 3, 4, 5};
    buffMan.publish(input);

    ASSERT_EQ(buffMan.peekBuffer(0), 1);
    ASSERT_EQ(buffMan.peekBuffer(1), 2);
    ASSERT_EQ(buffMan.peekBuffer(2), 3);
    ASSERT_EQ(buffMan.peekBuffer(3), 4);
    ASSERT_EQ(buffMan.peekBuffer(4), 5);
}

TEST(TestCircularBufferManager, DoubleParamPublish) {
    CircularBufferManager buffMan = CircularBufferManager<int>(5);

    for (int idx = 0; idx < 5; ++idx) {
        buffMan.publish(idx + 1, idx);
    }

    ASSERT_EQ(buffMan.peekBuffer(0), 1);
    ASSERT_EQ(buffMan.peekBuffer(1), 2);
    ASSERT_EQ(buffMan.peekBuffer(2), 3);
    ASSERT_EQ(buffMan.peekBuffer(3), 4);
    ASSERT_EQ(buffMan.peekBuffer(4), 5);
}

TEST(TestCircularManager, DoubleParamPublishInvalidInput) {
    CircularBufferManager buffMan = CircularBufferManager<int>(5);

    ASSERT_EQ(buffMan.publish(69, -420), 1);
    ASSERT_EQ(buffMan.publish(-420, 69), 1);
}

TEST(TestCircularBufferManager, PublishInputTooLong) {
    CircularBufferManager buffMan = CircularBufferManager<int>(4);

    std::vector<int> input = {1, 2, 3, 4, 5};
    ASSERT_THROW(buffMan.publish(input), std::invalid_argument);
}

TEST(TestCircularBufferManager, ImproperAccessBuffer) {
    CircularBufferManager<int> buffMan(5);

    ASSERT_THROW(buffMan.accessBuffer(69), std::out_of_range);
    ASSERT_THROW(buffMan.accessBuffer(5), std::out_of_range);
    ASSERT_THROW(buffMan.accessBuffer(-1), std::out_of_range);
}

TEST(TestCircularBufferManager, ImproperPeekBuffer) {
    CircularBufferManager<int> buffMan(5);

    ASSERT_THROW(buffMan.peekBuffer(69), std::out_of_range);
    ASSERT_THROW(buffMan.peekBuffer(5), std::out_of_range);
    ASSERT_THROW(buffMan.peekBuffer(-1), std::out_of_range);
}

TEST(TestCircularBufferManager, ProperAccessBuffer) {
    CircularBufferManager<int> buffMan(5);

    ASSERT_EQ(buffMan.accessBuffer(0).getSize(), 0);
    ASSERT_EQ(buffMan.accessBuffer(0).getCapacity(), 1024);
    
    ASSERT_EQ(buffMan.accessBuffer(1).getSize(), 0);
    ASSERT_EQ(buffMan.accessBuffer(1).getCapacity(), 1024);
}

TEST(TestCircularBufferManager, ConsumeAll) {
    CircularBufferManager<int> buffMan(5);

    buffMan.accessBuffer(0).push(0);
    buffMan.accessBuffer(1).push(1);
    buffMan.accessBuffer(2).push(2);
    buffMan.accessBuffer(3).push(3);
    buffMan.accessBuffer(4).push(4);

    std::vector<int> expected = {0,1,2,3,4};

    ASSERT_EQ(buffMan.consumeAll(), expected);
}
