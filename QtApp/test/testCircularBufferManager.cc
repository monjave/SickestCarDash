#include "gtest/gtest.h"
#include "CircularBufferManager.h"

// TODO
// accessBuffer() valid input
// consumeAll() 

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
