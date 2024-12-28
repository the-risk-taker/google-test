// NOTE: Taken from: https://github.com/ourarash/cpp-template

#include <gmock/gmock.h>

using ::testing::Each;
using ::testing::Truly;

bool IsPositive(int x)
{
    return x > 0;
}

TEST(MatchersTest, WithoutTruly)
{
    std::vector<double> v = {4, 6, 8, 2};

    for (auto& e : v)
    {
        EXPECT_TRUE(IsPositive(e));
        EXPECT_PRED1(IsPositive, e);
    }
}

TEST(MatchersTest, WithTruly)
{
    std::vector<double> v = {4, 6, 8, 2};
    EXPECT_THAT(v, Each(Truly(IsPositive)));
}
