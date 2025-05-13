#include "gtest/gtest.h"
#include "ReplayParser.h"

TEST(ReplayParserTest, FirstTest) {
    ReplayParser<std::string> newReplay("../../QtApp/replay/data/nurburgring_24h/data");
    //ASSERT_EQ(newReplay.getValue(), 3.0);
}

TEST(ReplayParserTest, ConfirmReplayData) {} // will finish

// test for if file location is invalid
