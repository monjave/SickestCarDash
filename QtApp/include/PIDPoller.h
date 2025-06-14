#ifndef PIDPOLLER_H
#define PIDPOLLER_H

#include <QObject>
#include <QString>
#include <QAtomicInt>

class PIDPoller : public QObject {
    Q_OBJECT
public:
    explicit PIDPoller(QObject *parent = nullptr);

    void stopPolling();

    signals: 
    void requestPid(const QString &pid);

    public slots:
    void startPolling();

    private:
    QAtomicInt running;
};
#endif // PIDPOLLER_H