// VehicleConnection.cpp
#include "VehicleConnection.h"

/* -- Change log --
    - Moved include for QDebug over to the header file
    - Added doxygen comments
*/

/// @brief Constructs a new VehicleConnection object with a parent QObject,
/// initializes the QTimer object, cmdIndex value to 0, and fills initCommands.
/// @details This constructor sets up a QSerialPort object, configures it, and
/// connects signals and slots for handling incoming data.
/// @param parent Give the new VehicleConnection a parent QObject, defaults to
/// nullptr

VehicleConnection::VehicleConnection(QObject *parent)
    : QObject(parent), serial(new QSerialPort(this)), cmdIndex(0) {
  QSerialPort *port = qobject_cast<QSerialPort *>(serial);
  if (port) {
    port->setPortName("/dev/ttyUSB0");
    configureSerialPort();
    if (!port->open(QIODevice::ReadWrite)) {
      emit errorOccurred("Failed to open serial port: " + port->errorString());
      return;
    }
  }

  connect(serial, &QIODevice::readyRead, this,
          &VehicleConnection::handleReadyRead);
  connect(&initTimer, &QTimer::timeout, this,
          &VehicleConnection::sendNextInitCommand);

  initCommands = {"ATZ", "ATE0", "ATL0", "ATS0", "ATSP2"};
}

/// @brief Constructs a new VehicleConnection object with a mock QIODevice,
/// initializes the QTimer object, cmdIndex value to 0, and fills initCommands.
VehicleConnection::VehicleConnection(QIODevice *device, QObject *parent)
    : QObject(parent), serial(device), cmdIndex(0) {
  QSerialPort *port = qobject_cast<QSerialPort *>(serial);
  if (port && !port->isOpen()) {
    port->setPortName("/dev/ttyUSB0");
    configureSerialPort();
    if (!port->open(QIODevice::ReadWrite)) {
      emit errorOccurred("Failed to open mock serial port: " +
                         port->errorString());
      return;
    }
  }

  connect(serial, &QIODevice::readyRead, this,
          &VehicleConnection::handleReadyRead);
  qDebug() << "connecting serial to handleReadyRead";
  connect(&initTimer, &QTimer::timeout, this,
          &VehicleConnection::sendNextInitCommand);
  qDebug() << "connecting initTimer to sendNextInitCommand";

  initCommands = {"ATZ", "ATE0", "ATL0", "ATS0", "ATSP2"};
}

/// @brief Configure the serial port settings if needed
void VehicleConnection::configureSerialPort() {
  QSerialPort *port = qobject_cast<QSerialPort *>(serial);
  if (!port) {
    return;
  }
  port->setBaudRate(QSerialPort::Baud115200);
  port->setDataBits(QSerialPort::Data8);
  port->setParity(QSerialPort::NoParity);
  port->setStopBits(QSerialPort::OneStop);
  port->setFlowControl(QSerialPort::NoFlowControl);
  port->setReadBufferSize(1024);
}

/// @brief Write a command to the QSerialPort object
/// @param command The command to be written passed in as a QString object
/// @note toLatin1() converts QString to QByteArray better suited for raw hex
void VehicleConnection::sendCommand(const QString &command) {
  if (serial->isOpen()) {
    qDebug() << "sendCommand serial->isOpen == true";
    QString fullCommand = command + "\r";
    serial->write(fullCommand.toLatin1());
  }
}

/// @brief Begins the initialization sequence by initializing cmdIndex and
/// starting a QTimer for 1 second
void VehicleConnection::beginInitSequence() {
  cmdIndex = 0;
  qDebug() << "beginningInitSequence";
  initTimer.start(1000);  // Send each command 1 second apart
}

/// @brief A slot that writes the next initCommand to the QSerialPort object.
/// @note Delete initTimer after initialization is complete if we need to
/// optimize memory usage?
void VehicleConnection::sendNextInitCommand() {
  if (cmdIndex < initCommands.size()) {
    while (cmdIndex < initCommands.size()) {
      sendCommand(initCommands[cmdIndex]);
      qDebug() << "Init Command sent: " << initCommands[cmdIndex];
      cmdIndex++;
    }
  } else {
    initTimer.stop();
    qDebug() << "emitting initComplete";
    emit initComplete();
  }
}

/// @brief A slot that processes responses from QSerialPort and emits a
/// rawHexReceived signal
void VehicleConnection::handleReadyRead() {
  buffer.append(serial->readAll());
  qDebug() << "Handle ready read data:" << buffer.toHex(' ');

  int endIndex = buffer.indexOf('\r');
  qDebug() << "endIndex Value: " << endIndex;
  while (endIndex != -1) {
    QByteArray responseBytes = buffer.left(endIndex);
    buffer.remove(0, endIndex + 1);  // Remove the processed response
    QString hexString = responseBytes.toHex(' ').toUpper();

    qDebug() << "emitting rawHexReceived";
    emit rawHexReceived(hexString);

    endIndex = buffer.indexOf('\r');
  }
}