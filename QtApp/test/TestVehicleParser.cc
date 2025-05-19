#include "gtest/gtest.h"
#include "VehicleParser.h"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <cstdio>
#include <stdio.h>

TEST(VehicleParser, ExtractData) {
    VehicleParser parser;

    // Valid short hex strings
    EXPECT_EQ(parser.ExtractData("0A"), 10);
    EXPECT_EQ(parser.ExtractData("1F"), 31);
    EXPECT_EQ(parser.ExtractData("FF"), 255);
    EXPECT_EQ(parser.ExtractData("00FF"), 255);
    EXPECT_EQ(parser.ExtractData("0"), 0);

    // Hex strings with higher bytes that get masked out
    EXPECT_EQ(parser.ExtractData("1234"), 0x34);          // 0x1234 & 0x00FF = 0x34
    EXPECT_EQ(parser.ExtractData("ABCD"), 0xCD);          // 0xABCD & 0x00FF = 0xCD
    EXPECT_EQ(parser.ExtractData("00AB"), 0xAB);          // 0x00AB & 0x00FF = 0xAB

    // Lowercase hex accepted
    EXPECT_EQ(parser.ExtractData("ff"), 255);
    EXPECT_EQ(parser.ExtractData("abcd"), 0xCD);
    EXPECT_EQ(parser.ExtractData("7fffffff"), 255);  // Max signed int

    // Overflow test (std::stoi throws std::nullopt)
    EXPECT_EQ(parser.ExtractData("deadbeef"), std::nullopt);  // Overflows int
    EXPECT_EQ(parser.ExtractData("FFFFFFFFF"), std::nullopt); // Too large

    // Invalid input
    EXPECT_EQ(parser.ExtractData("123Z"), std::nullopt); // Invalid character
    EXPECT_EQ(parser.ExtractData("G1"), std::nullopt);   // Invalid character
    EXPECT_EQ(parser.ExtractData(""), std::nullopt);     // Empty string
}

// TODO 
// Add getter/setter for _pidTable instead of using Request(). Will break as soon as Request() is implemented
TEST(VehicleParser, Initialization) {
    VehicleParser parser;

    EXPECT_EQ(parser.Request("RESET"), "ATZ");
    EXPECT_EQ(parser.Request("ECHOOFF"), "ATE0");
    EXPECT_EQ(parser.Request("NOLINEFEED"), "ATL0");
    EXPECT_EQ(parser.Request("NOSPACES"), "ATS0");
    EXPECT_EQ(parser.Request("AUTOPRTCL"), "ATSP0");

    EXPECT_EQ(parser.Request("SPEED"), "010D");
    EXPECT_EQ(parser.Request("RPM"), "010C");
    EXPECT_EQ(parser.Request("FUEL"), "012F");
    EXPECT_EQ(parser.Request("WATERTEMP"), "0105");
    EXPECT_EQ(parser.Request("THROTTLE"), "0111");
    EXPECT_EQ(parser.Request("OILTEMP"), "015C");
    EXPECT_EQ(parser.Request("GEAR"), "01A4");
    EXPECT_EQ(parser.Request("BATTVOLTS"), "0142");
    EXPECT_EQ(parser.Request("STOREDDTC"), "03");
}

TEST(VehicleParser, getPIDTable) {
    VehicleParser parser;

    EXPECT_EQ(parser.getPIDTable("SPEED").first, std::string("010D"));
    EXPECT_EQ(parser.getPIDTable("RPM").first, std::string("010C"));
    EXPECT_EQ(parser.getPIDTable("FUEL").first, std::string("012F"));
    EXPECT_EQ(parser.getPIDTable("WATERTEMP").first, std::string("0105"));
    EXPECT_EQ(parser.getPIDTable("THROTTLE").first, std::string("0111"));
    EXPECT_EQ(parser.getPIDTable("OILTEMP").first, std::string("015C"));
    EXPECT_EQ(parser.getPIDTable("GEAR").first, std::string("01A4"));
    EXPECT_EQ(parser.getPIDTable("BATTVOLTS").first, std::string("0142"));
    EXPECT_EQ(parser.getPIDTable("STOREDDTC").first, std::string("03"));

    // Test buffer assignments
    EXPECT_EQ(parser.getPIDTable("SPEED").second, 0);
    EXPECT_EQ(parser.getPIDTable("RPM").second, 1);
    EXPECT_EQ(parser.getPIDTable("FUEL").second, 2);
    EXPECT_EQ(parser.getPIDTable("WATERTEMP").second, 3);
    EXPECT_EQ(parser.getPIDTable("THROTTLE").second, 4);
    EXPECT_EQ(parser.getPIDTable("OILTEMP").second, 5);
    EXPECT_EQ(parser.getPIDTable("GEAR").second, 6);
    EXPECT_EQ(parser.getPIDTable("BATTVOLTS").second, 7);
    EXPECT_EQ(parser.getPIDTable("STOREDDTC").second, 8);

    EXPECT_EQ(parser.getPIDTable("RESET").second, -1);
    EXPECT_EQ(parser.getPIDTable("ECHOOFF").second, -1);
    EXPECT_EQ(parser.getPIDTable("NOLINEFEED").second, -1);
    EXPECT_EQ(parser.getPIDTable("NOSPACES").second, -1);
    EXPECT_EQ(parser.getPIDTable("AUTOPRTCL").second, -1);
}

// Need to mock response from OBD2?
// TEST(VehicleParser, Request) {
//     VehicleParser parser;
// }

// FormRequestString is a simple function and is also private, it's a pain in the ass to test and probably not worth it considering the complexity of the function.
// To test, we need to refactor the private logic into a testable helper class.

// TEST(VehicleParser, FormRequeststring) {
//     VehicleParser parser;
//     std::string code = parser.accessPIDTable("SPEED").first;
//     EXPECT_EQ(parser.FormRequestString(code), "010D\r");
//     // EXPECT_EQ(parser.FormRequestString(parser.accessPIDTable("SPEED")).first, "010D\r");
// }

TEST(VehicleParser, PublishToMiddleware) {
    VehicleParser parser;
    CircularBufferManager buffMan = CircularBufferManager<int>(10);
    
    int testVal = 69;
    std::string testKey = "SPEED";
    parser.PublishToMiddleware(buffMan, testVal, testKey);
    EXPECT_EQ(buffMan.peekBuffer(0), 69);

    std::string badKey = "jfdkl;asjfld";
    EXPECT_EQ(parser.PublishToMiddleware(buffMan, testVal, badKey), 1);
}

/*
 * relative location of realtime TRUE test files to these tests:
 *  ../../QtApp/replay/data/nurburgring_24h/data
 */

/**
 * @brief Create a Test CSV object
 * 
 * @param path 
 * @param contents 
 */
void createTestCSV(const std::string& path, const std::string& contents) {
  std::ofstream file(path, std::ios::out);
  if (!file.is_open()) {
    std::cerr << "File failed to open at " << path << "\n";
    return;
  }
  file << contents;
  file.close();
}

TEST(VehicleParser, HandlesMissingFile) {
  EXPECT_ANY_THROW(VehicleParser newReplay("bad_path.csv"));
}

TEST(VehicleParser, AllowsEmptyCSV) {
  std::string filePath = "../../QtApp/test/build/Debug";
  std::string fileName = filePath + "/empty.csv";
  createTestCSV(fileName, "");
  VehicleParser newReplay(filePath);
  auto& data = newReplay.getData();

  std::fstream file(fileName);
  ASSERT_TRUE(file.is_open());
  file.close();
  ASSERT_EQ(data.size(), 0);
}

TEST(VehicleParser, LoadsValidCSV) {
  std::string filePath = "../../QtApp/test/build/Debug";
  std::string fileName = filePath + "/valid.csv";
  createTestCSV(fileName,
                "Time,Speed,Distance\n9.9,0.0,0.0\n1.1,1.1,1.1\n2.2,2.2,2.2\n6."
                "9,6.9,6.9\n4.20,4.20,4.20");

  std::ifstream checkFile(filePath);
  VehicleParser newReplay(filePath);

  auto& data = newReplay.getData();
  ASSERT_TRUE(data.count("Time") == 1);
  ASSERT_TRUE(data.count("Speed") == 1);
  ASSERT_TRUE(data.count("Distance") == 1);
  ASSERT_EQ(data["Time"].size(), 5);
  ASSERT_EQ(data["Speed"].size(), 5);
  ASSERT_EQ(data["Distance"].size(), 5);
}

TEST(VehicleParser, HandlesMalformedCSV) {
  std::string filePath = "../../QtApp/test/build/Debug";
  std::string fileName = filePath + "/malformed.csv";
  createTestCSV(
      fileName,
      "Time,Speed,Distance\n9.9,not_right,0.0\n1.1,1.1,1.1\n2.2,2.2,2.2\n6."
      "9,6.9,6.9\nincorrect,4.20,4.20");
  EXPECT_ANY_THROW(VehicleParser newReplay(filePath));
}
