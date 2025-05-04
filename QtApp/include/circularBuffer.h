#ifndef CIRCULARBUFFERS_H
#define CIRCULARBUFFERS_H

#include <vector>

template <class T>
class CircularBuffer {
private:
    int _size;
	std::vector<T> _buffer;
	int _start;
	int _end;

public:
    CircularBuffer(int capacity);
	int8_t push(T value);
	T pop();
	T peek() const;
	bool isEmpty() const;
	bool isFull() const;
	int getSize() const;
	int getCapacity() const;
};

#endif //CIRCULARBUFFERS_H
