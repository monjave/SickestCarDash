#ifndef QIODEVICE_H
#define QIODEVICE_H

class QIODevice : public QObject {
public:
    virtual bool open(OpenMode mode);
    virtual void close();
    virtual qint64 readData(char *data, qint64 maxlen) = 0;
    virtual qint64 writeData(const char *data, qint64 len) = 0;
};

#endif // QIODEVICE_H
