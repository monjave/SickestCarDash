//
// Created by Joshua Lo on 5/3/25.
//

/*
    Template classes not supported by Q_OBJECT, EVERYTHING IS NOW A DOUBLE
    Template classes not supported by Q_OBJECT, EVERYTHING IS NOW A DOUBLE
*/

#ifndef CIRCULARBUFFERMANAGER_H
#define CIRCULARBUFFERMANAGER_H

#include <vector>
#include "CircularBuffer.h"
#include <QObject>
#include <QObject>

#define BUFFER_SIZE 1024
#define BUFFERS_TO_INIT 9

class CircularBufferManager : public QObject {
    Q_OBJECT
#define BUFFERS_TO_INIT 9

class CircularBufferManager : public QObject {
    Q_OBJECT

private:
    std::vector<CircularBuffer<double>> _buffers;
    std::vector<double> _packet;
    std::vector<CircularBuffer<double>> _buffers;
    std::vector<double> _packet;
    void writeToBuffer();
    int _bufferByteSize;
    int _bufferCount;

private slots:

signals:
    // void dataReady();

public:
    CircularBufferManager(int numBuffers);
    ~CircularBufferManager();
    void publish(std::vector<double> values);
    int8_t publish(double data, int buffIdx);
    // std::vector<int> consumeAll();  // DEPRECATED PROBABLY
    ~CircularBufferManager();
    void publish(std::vector<double> values);
    int8_t publish(double data, int buffIdx);
    // std::vector<int> consumeAll();  // DEPRECATED PROBABLY
    // void packetReady();  // Wrte this if we decide on event-driven
    int getByteSize() const;
    int getBufferCount() const;
    std::optional<double> peekBuffer(int buffNum) const;
    CircularBuffer<double>& accessBuffer(int buffNum);
    std::optional<double> peekBuffer(int buffNum) const;
    CircularBuffer<double>& accessBuffer(int buffNum);
};

// #include "CircularBufferManager.cc"
// #include "CircularBufferManager.cc"
#endif //CIRCULARBUFFERMANAGER_H
