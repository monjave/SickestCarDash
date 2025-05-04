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
T CircularBuffer<T>::pop() {
    if (!isEmpty()) {
        _end = (_end - 1 + getCapacity()) % getCapacity();
        T toReturn = _buffer[_end]; 
        --_size;

        return toReturn;
    } else {
        // IMPLEMENT ACTUAL ERROR HANDLING OR SOMETHING?
        std::cout << "Cannot pop from an empty buffer!\n"; 
    }
}

/// @brief Returns the most recent element without removing it from the buffer.
/// @tparam T Type of elements stored in the buffer.
/// @return The most recently pushed element.
template <class T>
T CircularBuffer<T>::peek() const {
    if (!isEmpty()) {
        int idx = (_end - 1 + getCapacity()) % getCapacity(); 
        return _buffer[idx];  
    } else {
        // IMPLEMENT ACTUAL ERROR HANDLING OR SOMETHING?
        std::cout << "Cannot peek an empty buffer!\n";
    }
}

/// @brief Pushes a new element into the buffer.
/// @tparam T Type of elements stored in the buffer.
/// @param value 
/// @return 0 if the value was pushed without overwriting; -1 if it overwrote the oldest value.
template <class T>
int8_t CircularBuffer<T>::push(T value) {
    if (!isFull()) {
        _buffer[_end] = value;
        _end = (_end + 1) % _capacity;
        ++_size;

        return 0;
    } else {
        _buffer[_start] = value;
        _start = (_start + 1) % _capacity;
        _end = (_end + 1) % _capacity;
        
        return -1;
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
    return _size == _capacity;
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

template class CirculuarBuffer<int>;
template class CirculuarBuffer<uint8_t>;
template class CirculuarBuffer<long>;
template class CirculuarBuffer<long long>;
template class CirculuarBuffer<float>;
template class CirculuarBuffer<double>;