// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QObject>

#include "autogen/environment.h"
#include "CircularBufferManagerWrapper.h"
#include "FrontendConnection.h"

int main(int argc, char *argv[])
{
    set_qt_environment();
    QApplication app(argc, argv);

    qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Data", 1, 0, "CarData");
    qmlRegisterType<FrontendConnection>("FrontendConnection.Invokables", 1, 0, "FrontendConnection");

    //qmlRegisterSingletonType<CircularBufferManagerWrapper>("Car.Data", 1, 0, "CarData") [] (;

    //qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Data", 1, 0, "DataSpeed");
    //qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Data", 1, 0, "DataRPM");
    //qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Data", 1, 0, "DataFuel");
    //qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Data", 1, 0, "DataTemp");
    //qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Data", 1, 0, "DataCoolanttemp");
    //qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Data", 1, 0, "DataClock");
    //qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Data", 1, 0, "DataEnginetemp");
    //qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Data", 1, 0, "DataOilTemp");
    //qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Data", 1, 0, "DataGearShift");

    /*
    CircularBufferManagerWrapper data;
    std::cout << data.getSpeed() << std::endl;
    data.setSpeed(1);
    std::cout << data.getSpeed() << std::endl;
    engine.rootContext()->setContextProperty("data", &data);
    */

    QQmlApplicationEngine engine;
    const QUrl url(mainQmlFile);
    QObject::connect(
                &engine, &QQmlApplicationEngine::objectCreated, &app,
                [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");
    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
