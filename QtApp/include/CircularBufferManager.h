//
// Created by Joshua Lo on 5/3/25.
//

/*
    Need to determine how many buffers to initialize
*/

#ifndef CIRCULARBUFFERMANAGER_H
#define CIRCULARBUFFERMANAGER_H

#include <vector>
#include "CircularBuffer.h"

#define BUFFER_SIZE 1024
// #define BUFFERS_TO_INIT 1024

template <class T>
class CircularBufferManager {
private:
    std::vector<CircularBuffer<T>> _buffers;
    std::vector<T> _packet;
    void writeToBuffer();
    int _bufferByteSize;
    int _bufferCount;

public:
    CircularBufferManager(int numBuffers);
    void publish(std::vector<T> values);
    int8_t publish(T data, int buffIdx);
    std::vector<int> consumeAll();
    // void packetReady();  // Wrte this if we decide on event-driven
    int getByteSize() const;
    int getBufferCount() const;
    std::optional<T> peekBuffer(int buffNum) const;
    CircularBuffer<T>& accessBuffer(int buffNum);
};

#include "CircularBufferManager.cc"
#endif //CIRCULARBUFFERMANAGER_H
