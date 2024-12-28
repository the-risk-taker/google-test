#include <gtest/gtest.h>

TEST(HelloTest, BasicAssertionsOne)
{
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7 * 6, 42);
}
