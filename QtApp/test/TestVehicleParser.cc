#include <QtTest/QtTest>
#include <QtTest/QtTest>
#include "VehicleParser.h"
#include "CircularBuffer.h"
#include "CircularBuffer.h"
#include <fstream>

class VehicleParserTest : public QObject {
    Q_OBJECT

private slots:
    void ExtractData_data();
    void ExtractData();

    // void Initialization();
    void getPIDTable();
    void PublishToMiddleware();

    void HandlesMissingFile();
    // void AllowsEmptyCSV();
    // void LoadsValidCSV();
    // void HandlesMalformedCSV();

private:
    void createTestCSV(const std::string& path, const std::string& contents);
};

void VehicleParserTest::ExtractData_data() {
    QTest::addColumn<QString>("hexStr");
    QTest::addColumn<bool>("isValid");
    QTest::addColumn<int>("expectedValue");

    // Valid short hex strings
    QTest::newRow("0A") << "0A" << true << 10;
    QTest::newRow("1F") << "1F" << true << 31;
    QTest::newRow("FF") << "FF" << true << 255;
    QTest::newRow("00FF") << "00FF" << true << 255;
    QTest::newRow("0") << "0" << true << 0;

    // Hex strings with masking
    QTest::newRow("1234") << "1234" << true << 0x34;
    QTest::newRow("ABCD") << "ABCD" << true << 0xCD;
    QTest::newRow("00AB") << "00AB" << true << 0xAB;

    // Lowercase hex
    QTest::newRow("ff") << "ff" << true << 255;
    QTest::newRow("abcd") << "abcd" << true << 0xCD;
    QTest::newRow("7fffffff") << "7fffffff" << true << 255;

    // Invalid / malformed inputs
    QTest::newRow("deadbeef") << "deadbeef" << false << 0;
    QTest::newRow("FFFFFFFFF") << "FFFFFFFFF" << false << 0;
    QTest::newRow("123Z") << "123Z" << false << 0;
    QTest::newRow("G1") << "G1" << false << 0;
    QTest::newRow("empty") << "" << false << 0;
}


void VehicleParserTest::ExtractData() {
    QFETCH(QString, hexStr);
    QFETCH(bool, isValid);
    QFETCH(int, expectedValue);

    VehicleParser parser;
    auto [valid, value] = parser.ExtractData(hexStr.toStdString());

    QCOMPARE(valid, isValid);
    if (isValid)
        QCOMPARE(value, expectedValue);
}


// void VehicleParserTest::Initialization() {
//     VehicleParser parser;
//     VehicleConnection vc;
//     QCOMPARE(parser.Request("RESET"), "ATZ");
//     QCOMPARE(parser.Request("ECHOOFF"), "ATE0");
//     QCOMPARE(parser.Request("NOLINEFEED"), "ATL0");
//     QCOMPARE(parser.Request("NOSPACES"), "ATS0");
//     QCOMPARE(parser.Request("AUTOPRTCL"), "ATSP0");
//     QCOMPARE(parser.Request("SPEED"), "010D");
//     QCOMPARE(parser.Request("RPM"), "010C");
//     QCOMPARE(parser.Request("FUEL"), "012F");
//     QCOMPARE(parser.Request("WATERTEMP"), "0105");
//     QCOMPARE(parser.Request("THROTTLE"), "0111");
//     QCOMPARE(parser.Request("OILTEMP"), "015C");
//     QCOMPARE(parser.Request("GEAR"), "01A4");
//     QCOMPARE(parser.Request("BATTVOLTS"), "0142");
//     QCOMPARE(parser.Request("STOREDDTC"), "03");
// }

void VehicleParserTest::getPIDTable() {
    VehicleParser parser;
    std::vector<std::pair<QString, std::pair<std::string, int>>> tests = {
        {"SPEED", {"010D", 0}},
        {"RPM", {"010C", 1}},
        {"FUEL", {"012F", 2}},
        {"WATERTEMP", {"0105", 3}},
        {"THROTTLE", {"0111", 4}},
        {"OILTEMP", {"015C", 5}},
        {"GEAR", {"01A4", 6}},
        {"BATTVOLTS", {"0142", 7}},
        {"STOREDDTC", {"03", 8}},
        {"RESET", {"ATZ", -1}},
        {"ECHOOFF", {"ATE0", -1}},
        {"NOLINEFEED", {"ATL0", -1}},
        {"NOSPACES", {"ATS0", -1}},
        {"AUTOPRTCL", {"ATSP0", -1}},
    };

    for (const auto& [label, expected] : tests) {
        auto pid = parser.getPIDTable(label.toStdString());
        QCOMPARE(pid.first, expected.first);
        QCOMPARE(pid.second, expected.second);
    }
}

void VehicleParserTest::PublishToMiddleware() {
    VehicleParser parser;
    CircularBufferManager buffMan(10);

    int testVal = 69;
    std::string testKey = "SPEED";
    parser.PublishToMiddleware(buffMan, testVal, testKey);
    QCOMPARE(buffMan.peekBuffer(0), 69);

    std::string badKey = "INVALID_KEY";
    QCOMPARE(parser.PublishToMiddleware(buffMan, testVal, badKey), 1);
}

void VehicleParserTest::HandlesMissingFile() {
    QVERIFY_EXCEPTION_THROWN(VehicleParser("nonexistent_path.csv"), std::exception);
}

void VehicleParserTest::createTestCSV(const std::string& path, const std::string& contents) {
    qDebug() << "Working dir:" << QDir::currentPath();
    std::ofstream file(path);
    QVERIFY(file.is_open());
    file << contents;
    file.close();
}

// void VehicleParserTest::AllowsEmptyCSV() {
//     std::string filePath = "test_empty.csv";
//     createTestCSV(filePath, "");
//     qDebug() << "Working dir:" << QDir::currentPath();
//     VehicleParser replay(QDir::currentPath().toStdString() + "/" + filePath);
//     auto& data = replay.getData();
//     QCOMPARE(data.size(), size_t(0));
// }

// void VehicleParserTest::LoadsValidCSV() {
//     std::string filePath = "test_valid.csv";
//     createTestCSV(filePath, "Time,Speed,Distance\n9.9,0.0,0.0\n1.1,1.1,1.1\n2.2,2.2,2.2\n6.9,6.9,6.9\n4.20,4.20,4.20");
//     VehicleParser replay(filePath);
//     auto& data = replay.getData();

//     QVERIFY(data.count("Time") == 1);
//     QVERIFY(data.count("Speed") == 1);
//     QVERIFY(data.count("Distance") == 1);
//     QCOMPARE(data["Time"].size(), size_t(5));
//     QCOMPARE(data["Speed"].size(), size_t(5));
//     QCOMPARE(data["Distance"].size(), size_t(5));
// }

// void VehicleParserTest::HandlesMalformedCSV() {
//     std::string filePath = "test_malformed.csv";
//     createTestCSV(filePath, "Time,Speed,Distance\n9.9,not_right,0.0\n1.1,1.1,1.1\n2.2,2.2,2.2\n6.9,6.9,6.9\nincorrect,4.20,4.20");
//     QVERIFY_EXCEPTION_THROWN(VehicleParser(filePath), std::exception);
// }

QTEST_MAIN(VehicleParserTest)
#include "TestVehicleParser.moc"
