#ifndef QTIMER_H
#define QTIMER_H

class QTimer : public QObject {
public:
    void start(int msec);
    void stop();
    bool isActive() const;
};

#endif // QTIMER_H
