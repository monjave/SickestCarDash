// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QObject>

#include "autogen/environment.h"
#include "CircularBufferManagerWrapper.h"

int main(int argc, char *argv[])
{
    set_qt_environment();
    QApplication app(argc, argv);

    qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Speed", 1, 0, "DataSpeed");
    /*qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Speed", 1, 0, "DataSpeed");
    qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Speed", 1, 0, "DataSpeed");
    qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Speed", 1, 0, "DataSpeed");
    qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Speed", 1, 0, "DataSpeed");
    qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Speed", 1, 0, "DataSpeed");
    qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Speed", 1, 0, "DataSpeed");
    qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Speed", 1, 0, "DataSpeed");
    qmlRegisterType<CircularBufferManagerWrapper>("CircularBuffer.Speed", 1, 0, "DataSpeed"); */

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
