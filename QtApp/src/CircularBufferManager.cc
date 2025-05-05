#include "CircularBufferManager.h"

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

template <class T>
int CircularBufferManager<T>::getByteSize() const {
    return _bufferByteSize;
}

template <class T>
int CircularBufferManager<T>::getBufferCount() const {
    return _bufferCount;
}

template <class T>
void CircularBufferManager<T>::publish(std::vector<T> values) {
    if (_bufferCount != values.size()) {
        throw std::invalid_argument("Argument size does not match number of buffers");
    }
    for (int idx = 0; idx < values.size(); ++idx) {
        _buffers[idx].push(values[idx]);
    }
}

template <class T>
std::optional<T> CircularBufferManager<T>::peekBuffer(int buffNum) const {
    if (buffNum < 0 || buffNum >= _bufferCount) {
        throw std::out_of_range("Buffer index out of range");
    }
    return _buffers[buffNum].peek();
}

template <class T>
CircularBuffer<T>& CircularBufferManager<T>::accessBuffer(int buffNum) {
    if (buffNum < 0 || buffNum >= _bufferCount) {
        throw std::out_of_range("Buffer index out of range");
    }
    return _buffers[buffNum];
}

template class CircularBufferManager<int>;
template class CircularBufferManager<uint8_t>;
template class CircularBufferManager<long>;
template class CircularBufferManager<long long>;
template class CircularBufferManager<float>;
template class CircularBufferManager<double>;
template class CircularBufferManager<std::string>;
template class CircularBufferManager<char>;