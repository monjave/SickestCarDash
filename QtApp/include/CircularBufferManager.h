//
// Created by Joshua Lo on 5/3/25.
//

/*
    Need to determine how many buffers to initialize
*/

#ifndef CIRCULARBUFFERMANAGER_H
#define CIRCULARBUFFERMANAGER_H

#include <vector>

#define BUFFER_SIZE 1024

template <class T>
class CircularBufferManager {
private:
    std::vector<std::vector<T>> buffers;
    std::vector<T> _packet;
    int _bufferCount;
    void writeToBuffer();

public:
    CircularBufferManager(int numBuffers);
    int publish(std::vector<T> values);
    std::vector<T> consumeAll();
    // void packetReady();  // Wrte this if we decide on event-driven
};

#endif //CIRCULARBUFFERMANAGER_H
