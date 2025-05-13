#include <QGuiApplication>
#include <QQmlApplicationEngine>
//#include <QQmlContext>
#include "include/CircularBufferManagerWrapper.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Speed", 1, 0, "DataSpeed");

    QQmlApplicationEngine engine;

    /*
    CircularBufferManagerWrapper data;
    std::cout << data.getSpeed() << std::endl;
    data.setSpeed(1);
    std::cout << data.getSpeed() << std::endl;
    engine.rootContext()->setContextProperty("data", &data); */

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);
    engine.loadFromModule("QtApp", "Main");

    return app.exec();
}
