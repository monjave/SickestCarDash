#include "gtest/gtest.h"
#include "VehicleParser.h"

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

    // Overflow test (std::stoi throws)
    EXPECT_EQ(parser.ExtractData("deadbeef"), std::nullopt);  // Overflows int
    EXPECT_EQ(parser.ExtractData("FFFFFFFFF"), std::nullopt); // Too large

    // Invalid input
    EXPECT_EQ(parser.ExtractData("123Z"), std::nullopt); // Invalid character
    EXPECT_EQ(parser.ExtractData("G1"), std::nullopt);   // Invalid character
    EXPECT_EQ(parser.ExtractData(""), std::nullopt);     // Empty string
}


// Need to mock response from OBD2?
TEST(VehicleParser, Request) {
    VehicleParser parser;

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

TEST(VehicleParser, FormRequeststring) {
    VehicleParser parser;
}