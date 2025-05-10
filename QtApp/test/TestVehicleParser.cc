#include "gtest/gtest.h"
#include "VehicleParser.h"

TEST(VehicleParser, convertHexToInt) {
    VehicleParser parser;

    // Valid hexadecimal strings
    EXPECT_EQ(parser.ConvertHexToInt("0A"), 10);
    EXPECT_EQ(parser.ConvertHexToInt("1F"), 31);
    EXPECT_EQ(parser.ConvertHexToInt("FF"), 255);
    EXPECT_EQ(parser.ConvertHexToInt("7fffffff"), 2147483647); // max signed int
    EXPECT_EQ(parser.ConvertHexToInt("0"), 0);

    // Lowercase hex (stoi accepts both)
    EXPECT_EQ(parser.ConvertHexToInt("ff"), 255);
    EXPECT_EQ(parser.ConvertHexToInt("deadbeef"), std::nullopt); // overflows signed int, expect nullopt

    // Invalid hexadecimal strings
    EXPECT_EQ(parser.ConvertHexToInt("G1"), std::nullopt);      // Invalid character
    EXPECT_EQ(parser.ConvertHexToInt("123Z"), std::nullopt);    // Invalid character
    EXPECT_EQ(parser.ConvertHexToInt(""), std::nullopt);        // Empty string

    // Overflow test (larger than int max)
    EXPECT_EQ(parser.ConvertHexToInt("FFFFFFFFF"), std::nullopt);
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