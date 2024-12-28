// NOTE: Taken from: https://github.com/ourarash/cpp-template

#include <gmock/gmock.h>
#include <regex>

TEST(MatchersTest, NoMatchers)
{
    std::string test_string = "Hello, this as a test string. We are here to help!";
    EXPECT_TRUE(test_string.rfind("Hello") == 0);
    EXPECT_TRUE(std::regex_match(test_string, std::regex(".*is.*help.*")));

    int test_value = 10;
    EXPECT_GT(test_value, 0);
    EXPECT_LT(test_value, 100);
}

TEST(MatchersTest, MatchersUsed)
{
    std::string test_string = "Hello, this as a test string. We are here to help!";
    EXPECT_THAT(test_string, testing::StartsWith("Hello"));
    EXPECT_THAT(test_string, testing::MatchesRegex(".*is.*help.*"));

    int test_value = 10;
    EXPECT_THAT(test_value, testing::AllOf(testing::Gt(0), testing::Lt(100)));
}
