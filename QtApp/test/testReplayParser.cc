#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include "ReplayParser.h"
#include "gtest/gtest.h"

/*
 * relative location of realtime TRUE test files to these tests:
 *  ../../QtApp/replay/data/nurburgring_24h/data
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

TEST(ReplayParserTest, LoadsValidCSV) {
  std::string filePath = "../../QtApp/test/build/Debug";
  std::string fileName = filePath + "/valid.csv";
  createTestCSV(fileName,
                "Time,Speed,Distance\n9.9,0.0,0.0\n1.1,1.1,1.1\n2.2,2.2,2.2\n6."
                "9,6.9,6.9\n4.20,4.20,4.20");

  std::ifstream checkFile(filePath);
  ReplayParser<std::string> newReplay(filePath);

  auto& data = newReplay.getData();
  ASSERT_TRUE(data.count("Time") == 1);
  ASSERT_TRUE(data.count("Speed") == 1);
  ASSERT_TRUE(data.count("Distance") == 1);
  ASSERT_EQ(data["Time"].size(), 5);
  ASSERT_EQ(data["Speed"].size(), 5);
  ASSERT_EQ(data["Distance"].size(), 5);
}

TEST(ReplayParserTest, HandlesMissingFile) {
  EXPECT_ANY_THROW(ReplayParser<double> newReplay("bad_path.csv"));
}

TEST(ReplayParserTest, HandlesMalformedCSV) {
  std::string filePath = "../../QtApp/test/build/Debug";
  std::string fileName = filePath + "/valid.csv";
  createTestCSV(
      fileName,
      "Time,Speed,Distance\n9.9,not_right,0.0\n1.1,1.1,1.1\n2.2,2.2,2.2\n6."
      "9,6.9,6.9\nincorrect,4.20,4.20");
  EXPECT_ANY_THROW(ReplayParser<double> newReplay(filePath));
}

TEST(ReplayParserTest, AllowsEmptyCSV) {
  std::string filePath = "../../QtApp/test/build/Debug";
  std::string fileName = filePath + "/valid.csv";
  createTestCSV(fileName, "");
  ReplayParser<std::string> newReplay(filePath);
  auto& data = newReplay.getData();

  ASSERT_EQ(data.size(), 0);
}

// TEST(ReplayParserTest, ) {}

// test for if file location is invalid
