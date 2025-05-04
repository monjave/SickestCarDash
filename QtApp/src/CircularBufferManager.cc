#include "CircularBufferManager.h"

template <class T>
CircularBufferManager<T>::CircularBufferManager(int numBuffers) {
    _bufferCount = numBuffers;

    for (int idx = 0; idx < _bufferCount; ++idx) {
        std::vector<T> newBuffer;
        newBuffer.resize(BUFFER_SIZE);
        buffers.push_back(newBuffer);
    }
}