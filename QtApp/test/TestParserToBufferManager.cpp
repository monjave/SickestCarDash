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
    VehicleParser parser("../../QtApp/test/files/mock_data/brief_mock_data_5_sec");
    parser.replayStart();

    QTest::qWait(40);

    CircularBufferManager* buffMan = parser.getBufferManager();
    auto valSpeed = buffMan->peekBuffer(0); // speed
    auto valThrottle = buffMan->peekBuffer(4); // throttle
    auto valRPM = buffMan->peekBuffer(1); // rpms

    QVERIFY(valSpeed.has_value());
    QVERIFY(valThrottle.has_value());
    QVERIFY(valRPM.has_value());

    // QCOMPARE(valSpeed.value(), 0.15);
    // QCOMPARE(valThrottle.value(), 50);
    // QCOMPARE(valRPM.value(), 15);

    QTest::qWait(60);
    auto valGear = buffMan->peekBuffer(6); // gear
    QVERIFY(valGear.has_value());
    // QCOMPARE(valGear.value(), 1);

    //QTest::qWait(20);
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

/*
      {"SPEED", {"010D", 0}},      // Buffer 0
      {"RPM", {"010C", 1}},        // Buffer 1
      {"FUEL", {"012F", 2}},       // Buffer 2
      {"WATERTEMP", {"0105", 3}},  // Buffer 3
      {"THROTTLE", {"0111", 4}},   // Buffer 4
      {"OILTEMP", {"015C", 5}},    // Buffer 5
      {"GEAR", {"01A4", 6}},       // Buffer 6
      {"BATTVOLTS", {"0142", 7}},  // Buffer 7
      {"STOREDDTC", {"03", 8}}     // Buffer 8
*/