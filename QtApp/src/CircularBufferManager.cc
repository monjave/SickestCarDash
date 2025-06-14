#include "CircularBufferManager.h"

CircularBufferManager::CircularBufferManager(int numBuffers) {
    _bufferCount = numBuffers;
    _bufferByteSize = 0;

    for (int idx = 0; idx < _bufferCount; ++idx) {
        CircularBuffer<double> newBuffer(BUFFER_SIZE);
        _buffers.push_back(newBuffer);
        _bufferByteSize += sizeof(double) * BUFFER_SIZE;
    }
}

int CircularBufferManager::getByteSize() const {

    return _bufferByteSize;
}

int CircularBufferManager::getBufferCount() const {
    return _bufferCount;
}

void CircularBufferManager::publish(std::vector<double> values) {

    if (_bufferCount != values.size()) {
        throw std::invalid_argument("Argument size does not match number of buffers");
    }
    for (int idx = 0; idx < values.size(); ++idx) {
        _buffers[idx].push(values[idx]);
    }
}

int8_t CircularBufferManager::publish(double data, int buffIdx) {

    if (buffIdx >= _bufferCount || buffIdx < 0) {
        std::cout << "Invalid buffer index provided to publish()";
        return 1;
    }

    return _buffers[buffIdx].push(data);
}

std::optional<double> CircularBufferManager::peekBuffer(int buffNum) const {

    if (buffNum < 0 || buffNum >= _bufferCount) {
        throw std::out_of_range("Buffer index out of range");
    }
    return _buffers[buffNum].peek();
}

CircularBuffer<double>& CircularBufferManager::accessBuffer(int buffNum) {

    if (buffNum < 0 || buffNum >= _bufferCount) {
        throw std::out_of_range("Buffer index out of range");
    }
    return _buffers[buffNum];
}

CircularBufferManager::~CircularBufferManager() = default;
