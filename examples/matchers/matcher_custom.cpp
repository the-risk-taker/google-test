// NOTE: Taken from: https://github.com/ourarash/cpp-template

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

using ::testing::Each;
using ::testing::Not;
using ::testing::PrintToString;

MATCHER_P(IsDivisibleBy, n, "")
{
    *result_listener << "where the remainder is " << (arg % n);   // NOTE: Mind 'result_listener' provided by GoogleTest
    return (arg % n) == 0;                                        // NOTE: Mind 'arg' provided by GoogleTest
}

TEST(CustomMatcher, CustomMatcher_ResultListener)
{
    EXPECT_THAT(9, IsDivisibleBy(3));

    std::vector<int> v = {4, 8, 12, 16, 20};
    EXPECT_THAT(v, Each(IsDivisibleBy(4)));
}

MATCHER_P2(IsBetween, a, b, (std::string(negation ? "Isn't" : "Is") + " between " + PrintToString(a) + " and " + PrintToString(b)))
{
    return a <= arg && arg <= b;
}

TEST(CustomMatcher, CustomMatcher_WithDescriptionString)
{
    EXPECT_THAT(10, IsBetween(9, 11));
    EXPECT_THAT(100, Not(IsBetween(9, 11)));
}
