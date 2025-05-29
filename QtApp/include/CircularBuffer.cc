#include "CircularBuffer.h"

/// @brief Constructs a CirculuarBuffer object with the given capacity. 
/// @tparam T Type of elements stored in the buffer.
/// @param capacity Maximum number of elements the buffer can hold.
template <class T>
CircularBuffer<T>::CircularBuffer(int capacity) {
    _size = 0;
    _buffer.resize(capacity);
    _start = 0;
    _end = 0;
}

/// @brief Removes and returns the most recent element in the buffer.
/// @tparam T Type of elements stored in the buffer.
/// @return The most recently pushed element.
/// @note Wraps around if necessary.
template <class T>
std::optional<T> CircularBuffer<T>::pop() {
    if (!isEmpty()) {
        _end = (_end - 1 + getCapacity()) % getCapacity();
        T toReturn = _buffer[_end]; 
        --_size;

        return toReturn;
    } else {
        return std::nullopt;
    }
}

/// @brief Returns the most recent element without removing it from the buffer.
/// @tparam T Type of elements stored in the buffer.
/// @return The most recently pushed element.
template <class T>
std::optional<T> CircularBuffer<T>::peek() const {
    if (!isEmpty()) {
        int idx = (_end - 1 + getCapacity()) % getCapacity(); 
        return _buffer[idx];  
    } else {
        return std::nullopt;
    }
}

/// @brief Pushes a new element into the buffer.
/// @tparam T Type of elements stored in the buffer.
/// @param value 
/// @return 0 if the value was pushed without overwriting; 1 if it overwrote the oldest value.
template <class T>
int8_t CircularBuffer<T>::push(T value) {
    if (!isFull()) {
        _buffer[_end] = value;
        _end = (_end + 1) % getCapacity();
        ++_size;

        return 0;
    } else {
        _buffer[_start] = value;
        _start = (_start + 1) % getCapacity();
        _end = (_end + 1) % getCapacity();
        
        return 1;
    }
}

/// @brief Check if the buffer is empty.
/// @tparam T Type of elements stored in the buffer.
/// @return Returns True if the buffer is empty and False if it is not empty.
template <class T>
bool CircularBuffer<T>::isEmpty() const {
    return _size == 0;
}

/// @brief Check if the buffer is full.
/// @tparam T Type of elements stored in the buffer.
/// @return Returns True if the buffer is full and False if it is not full.
template <class T>
bool CircularBuffer<T>::isFull() const {
    return _size == getCapacity();
}

/// @brief Get the size of the buffer.
/// @tparam T Type of elements stored in the buffer. 
/// @return Returns an int containing the size of the buffer.
template <class T>
int CircularBuffer<T>::getSize() const {
    return _size;
}

/// @brief Get the capacity of the buffer.
/// @tparam T Type of elements stored in the buffer.
/// @return Returns an int with the capacity of the buffer.
template <class T>
int CircularBuffer<T>::getCapacity() const {
    return _buffer.size();
}

/// @brief Print the state of the buffer.
/// @tparam T 
template <class T>
void CircularBuffer<T>::printBuffer() const {
    std::cout << "Buffer: ";
    for (auto& val : _buffer) {
        std::cout << val << ", ";
    }
    std::cout << "\n";
    std::cout << "Start: " << _start << "\n";
    std::cout << "End: " << _end << "\n";
}

// template class CircularBuffer<int>;
// template class CircularBuffer<uint8_t>;
// template class CircularBuffer<int8_t>;
// template class CircularBuffer<long>;
// template class CircularBuffer<long long>;
// template class CircularBuffer<float>;
// template class CircularBuffer<double>;
// template class CircularBuffer<std::string>;
// template class CircularBuffer<char>;
