#include "../include/CircularBufferManager.h"

/// @brief Constructs a CircularBufferManager object to hold a number of CircularBuffer objects.
/// @tparam T type of elements stored in the buffer.
/// @param numBuffers The number of CircularBuffer objects to initialize.
template <class T>
CircularBufferManager<T>::CircularBufferManager(int numBuffers) {
    _bufferCount = numBuffers;
    _bufferByteSize = 0;

    for (int idx = 0; idx < _bufferCount; ++idx) {
        CircularBuffer<T> newBuffer(BUFFER_SIZE);
        _buffers.push_back(newBuffer);
        _bufferByteSize += sizeof(T) * BUFFER_SIZE;
    }
}

/// @brief Get the combined byte size of all the buffers. 
/// @tparam T type of elements stored in the buffer.
/// @return Returns the combined byte size of all the buffers.
template <class T>
int CircularBufferManager<T>::getByteSize() const {
    return _bufferByteSize;
}

/// @brief Get the number of buffers managed by the CircularBufferManager.
/// @tparam T type of elements stored in the buffer.
/// @return Returns the number of buffers.
template <class T>
int CircularBufferManager<T>::getBufferCount() const {
    return _bufferCount;
}

/// @brief Push values to the CircularBuffer objects.
/// @tparam T type of elements stored in the buffer. 
/// @param values A vector of values holding data that needs to be pushed to the buffers.
// TODO
// If there is no value to update, then don't push anything to the idx'th buffer
template <class T>
void CircularBufferManager<T>::publish(std::vector<T> values) {
    if (_bufferCount != values.size()) {
        throw std::invalid_argument("Argument size does not match number of buffers");
    }
    for (int idx = 0; idx < values.size(); ++idx) {
        _buffers[idx].push(values[idx]);
    }
}

/// @brief Push a single value to the CircularBuffer object.
/// @tparam T type of elements stored in the buffer. 
/// @param data The data to be pushed to the CircularBuffer object.
/// @param buffIdx The index of the target buffer to be pushed to.
/// @return Returns a 0 if the publish was successful, otherwise return a 1;
template <class T>
int8_t CircularBufferManager<T>::publish(T data, int buffIdx) {
    if (buffIdx >= _bufferCount || buffIdx < 0) {
        std::cout << "Invalid buffer index provided to publish()";
        return 1;
    }

    return _buffers[buffIdx].push(data);
}

/// @brief Returns the most recent value for a given buffer.
/// @tparam T type of elements stored in the buffer. 
/// @param buffNum The idx of the buffer to be accessed.
/// @return Returns the most recent value for a given buffer.
template <class T>
std::optional<T> CircularBufferManager<T>::peekBuffer(int buffNum) const {
    if (buffNum < 0 || buffNum >= _bufferCount) {
        throw std::out_of_range("Buffer index out of range");
    }
    return _buffers[buffNum].peek();
}

/// @brief Access a buffer in the BufferManager.
/// @tparam T type of elements stored in the buffer. 
/// @param buffNum The idx of the buffer to be accessed. 
/// @return Returns the buffer stored at the buffNum idx in BufferManager.
template <class T>
CircularBuffer<T>& CircularBufferManager<T>::accessBuffer(int buffNum) {
    if (buffNum < 0 || buffNum >= _bufferCount) {
        throw std::out_of_range("Buffer index out of range");
    }
    return _buffers[buffNum];
}

/// @brief Get the most recent data from all buffers.
/// @tparam T type of elements stored in the buffer.  
/// @return A vector of ints holding the most recent data from all buffers. Index 0 holds buffer 0's data, Index 1 holds buffer 1's data, ... , Index n holds buffer n's data.
template <class T>
std::vector<int> CircularBufferManager<T>::consumeAll() {
    std::vector<int> packet;

    for (auto& buffer : _buffers) {
        std::optional<T> val = buffer.pop();
        if (val.has_value()) {
            packet.push_back(*val);
        } else {
            packet.push_back(-1);
        }
    }

    return packet;
}

template class CircularBufferManager<int>;
template class CircularBufferManager<uint8_t>;
template class CircularBufferManager<int8_t>;
template class CircularBufferManager<long>;
template class CircularBufferManager<long long>;
template class CircularBufferManager<float>;
template class CircularBufferManager<double>;
// template class CircularBufferManager<std::string>;
template class CircularBufferManager<char>;
