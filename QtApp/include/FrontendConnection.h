#ifndef FRONTENDCONNECTION_H
#define FRONTENDCONNECTION_H

#include <QObject>
#include <QDir>
#include "VehicleParser.h"
#include "CircularBufferManagerWrapper.h"
#include "VehicleSystemManager.h"


class FrontendConnection : public QObject {
    Q_OBJECT

    Q_PROPERTY(CircularBufferManagerWrapper* data READ data CONSTANT)

public:
    explicit FrontendConnection(CircularBufferManagerWrapper* dataProperties, QObject *parent = nullptr);
    ~FrontendConnection();

    CircularBufferManagerWrapper* data() const;

    std::string _replayPath = "../../QtApp/replay/data/example_nurburgring_24h/data";

    //Q_INVOKABLE void togglePaused();

private slots:
    //void startReplay();

public slots:
    void dataReady(int buffNum, double value);

private:
    //VehicleParser* carData;
    VehicleSystemManager* systemManager;

    CircularBufferManagerWrapper* dataProperties;
};

#endif // FRONTENDCONNECTION_H
