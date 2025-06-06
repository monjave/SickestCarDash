#ifndef FRONTENDCONNECTION_H
#define FRONTENDCONNECTION_H

#include <QObject>
#include <QDir>
#include "VehicleParser.h"
#include "CircularBufferManagerWrapper.h"

class FrontendConnection : public QObject {
    Q_OBJECT

public:
    explicit FrontendConnection(QObject *parent = nullptr);

    ~FrontendConnection();

    CircularBufferManagerWrapper* getDataProperties() {
        return dataProperties;
    }

    std::string _replayPath = "../../QtApp/replay/data/example_nurburgring_24h/data";

    Q_INVOKABLE void togglePaused();

signals:
    void togglePausedChanged(bool paused);

private slots:
    void increment();
    void geartime();
    void startReplay();
    void dataReady(int buffNum, double value);

private:
    //QTimer *timer;
    //QTimer *timerIcons;

    VehicleParser* carData;
    CircularBufferManagerWrapper* dataProperties;
};

#endif // FRONTENDCONNECTION_H
