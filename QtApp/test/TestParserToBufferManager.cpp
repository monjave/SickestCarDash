#include <QtTest/QtTest>
#include <QDir>
#include <QTimer>
#include "VehicleParser.h"
#include "CircularBufferManager.h"
#include <fstream>


class TestParserToBufferManager : public QObject {
    Q_OBJECT
    //createTestCSV(filePath, "Time,Speed,Distance\n9.9,0.0,0.0\n1.1,1.1,1.1\n2.2,2.2,2.2\n6.9,6.9,6.9\n4.20,4.20,4.20");
    //VehicleParser _parser("testFiles/here"); //! decide what to do with the test file location

private slots:
    void ReplayTimersFire();
    void BuffersReceiveData();
    void ReplayStopsWhenEmpty();
    void ValuesPushedToBufferInCorrectOrder();


private:
    void createTestCSV(const std::string& path, const std::string& contents);
};

void TestParserToBufferManager::ReplayTimersFire(){

}

void TestParserToBufferManager::BuffersReceiveData(){

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