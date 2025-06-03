#include <QtTest/QtTest>
#include <QDir>
#include <QTimer>
#include "VehicleParser.h"
#include "CircularBufferManager.h"
#include <fstream>


class TestParserToBufferManager : public QObject {
    Q_OBJECT

private slots:
    void BuffersReceiveCorrectData();
    void ReplayStopsWhenEmpty();
    void ValuesPushedToBufferInCorrectOrder();

private:
    void createTestCSV(const std::string& path, const std::string& contents);

public:
    // VehicleParser _parser("../../QtApp/test/files/mock_data/brief_mock_data_5_sec"); 
    // CircularBufferManager _buffMan(9);
};

void TestParserToBufferManager::BuffersReceiveCorrectData(){

}

void TestParserToBufferManager::ReplayStopsWhenEmpty(){

}

void TestParserToBufferManager::ValuesPushedToBufferInCorrectOrder(){

}


void TestParserToBufferManager::createTestCSV(const std::string& path, const std::string& contents) {
    qDebug() << "Working dir:" << QDir::currentPath();
    std::ofstream file(path);
    QVERIFY(file.is_open());
    file << contents;
    file.close();
}

QTEST_MAIN(TestParserToBufferManager)
#include "TestParserToBufferManager.moc"