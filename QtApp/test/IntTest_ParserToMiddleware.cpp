#include <QtTest/QtTest>
#include <QDir>
#include <QTimer>
#include "VehicleParser.h"
#include "CircularBufferManager.h"
#include <fstream>


class VehicleParserTest : public QObject {
    Q_OBJECT

private slots:
    void ExtractData_data();
    void ExtractData();

    void getPIDTable();
    void PublishToMiddleware();

private:
    void createTestCSV(const std::string& path, const std::string& contents);
};