#include "CircularBufferManager.h"

/// @brief Constructs a CircularBufferManager object to hold a number of CircularBuffer objects.
/// @param numBuffers The number of CircularBuffer objects to initialize.
CircularBufferManager::CircularBufferManager(int numBuffers) {
    _bufferCount = numBuffers;
    _bufferByteSize = 0;

    for (int idx = 0; idx < _bufferCount; ++idx) {
        CircularBuffer<double> newBuffer(BUFFER_SIZE);
        _buffers.push_back(newBuffer);
        _bufferByteSize += sizeof(double) * BUFFER_SIZE;
    }
}

/// @brief Get the combined byte size of all the buffers. 
/// @return Returns the combined byte size of all the buffers.
int CircularBufferManager::getByteSize() const {
    return _bufferByteSize;
}

/// @brief Get the number of buffers managed by the CircularBufferManager.
/// @return Returns the number of buffers.
int CircularBufferManager::getBufferCount() const {
    return _bufferCount;
}

/// @brief Push values to the CircularBuffer objects.
/// @param values A vector of values holding data that needs to be pushed to the buffers.
// TODO
// If there is no value to update, then don't push anything to the idx'th buffer
void CircularBufferManager::publish(std::vector<double> values) {
    if (_bufferCount != values.size()) {
        throw std::invalid_argument("Argument size does not match number of buffers");
    }
    for (int idx = 0; idx < values.size(); ++idx) {
        _buffers[idx].push(values[idx]);
    }
}

/// @brief Push a single value to the CircularBuffer object.
/// @param data The data to be pushed to the CircularBuffer object.
/// @param buffIdx The index of the target buffer to be pushed to.
/// @return Returns a 0 if the publish was successful, otherwise return a 1;
int8_t CircularBufferManager::publish(double data, int buffIdx) {
    if (buffIdx >= _bufferCount || buffIdx < 0) {
        std::cout << "Invalid buffer index provided to publish()";
        return 1;
    }

    return _buffers[buffIdx].push(data);
}

/// @brief Returns the most recent value for a given buffer.
/// @param buffNum The idx of the buffer to be accessed.
/// @return Returns the most recent value for a given buffer.
std::optional<double> CircularBufferManager::peekBuffer(int buffNum) const {
    if (buffNum < 0 || buffNum >= _bufferCount) {
        throw std::out_of_range("Buffer index out of range");
    }
    return _buffers[buffNum].peek();
}

/// @brief Access a buffer in the BufferManager.
/// @param buffNum The idx of the buffer to be accessed. 
/// @return Returns the buffer stored at the buffNum idx in BufferManager.
CircularBuffer<double>& CircularBufferManager::accessBuffer(int buffNum) {
    if (buffNum < 0 || buffNum >= _bufferCount) {
        throw std::out_of_range("Buffer index out of range");
    }
    return _buffers[buffNum];
}

/// @brief Get the most recent data from all buffers. 
/// @return A vector of ints holding the most recent data from all buffers. Index 0 holds buffer 0's data, Index 1 holds buffer 1's data, ... , Index n holds buffer n's data.
// std::vector<int> CircularBufferManager::consumeAll() {
//     std::vector<int> packet;

//     for (auto& buffer : _buffers) {
//         std::optional<T> val = buffer.pop();
//         if (val.has_value()) {
//             packet.push_back(*val);
//         } else {
//             packet.push_back(-1);
//         }
//     }

//     return packet;
// }

// void CircularBufferManager::dataReady() {

// }

CircularBufferManager::~CircularBufferManager() = default;