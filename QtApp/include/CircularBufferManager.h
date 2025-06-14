//
// Created by Joshua Lo on 5/3/25.
//

/*
    Template classes not supported by Q_OBJECT, EVERYTHING IS NOW A DOUBLE
*/

#ifndef CIRCULARBUFFERMANAGER_H
#define CIRCULARBUFFERMANAGER_H
#include <QObject>
#include <vector>
#include "CircularBuffer.h"

#define BUFFER_SIZE 1024
#define BUFFERS_TO_INIT 9

class CircularBufferManager : public QObject {
  Q_OBJECT

 private:
  std::vector<CircularBuffer<double>> _buffers;
  std::vector<double> _packet;
  void writeToBuffer();
  int _bufferByteSize;
  int _bufferCount;

 private slots:

 signals:
  void dataReady();

 public:
  /// @brief Constructs a CircularBufferManager object to hold a number of
  /// CircularBuffer objects.
  /// @param numBuffers The number of CircularBuffer objects to initialize.
  CircularBufferManager(int numBuffers);
  ~CircularBufferManager();

  /// @brief Push values to the CircularBuffer objects.
  /// @param values A vector of values holding data that needs to be pushed to
  /// the buffers.
  void publish(std::vector<double> values);

  /// @brief Push a single value to the CircularBuffer object.
  /// @param data The data to be pushed to the CircularBuffer object.
  /// @param buffIdx The index of the target buffer to be pushed to.
  /// @return Returns a 0 if the publish was successful, otherwise return a 1;
  int8_t publish(double data, int buffIdx);

  /// @brief Get the combined byte size of all the buffers.
  /// @return Returns the combined byte size of all the buffers.
  int getByteSize() const;

  /// @brief Get the number of buffers managed by the CircularBufferManager.
  /// @return Returns the number of buffers.
  int getBufferCount() const;

  /// @brief Returns the most recent value for a given buffer.
  /// @param buffNum The idx of the buffer to be accessed.
  /// @return Returns the most recent value for a given buffer.
  std::optional<double> peekBuffer(int buffNum) const;

  /// @brief Access a buffer in the BufferManager.
  /// @param buffNum The idx of the buffer to be accessed.
  /// @return Returns the buffer stored at the buffNum idx in BufferManager.
  CircularBuffer<double>& accessBuffer(int buffNum);
};

#endif  // CIRCULARBUFFERMANAGER_H
