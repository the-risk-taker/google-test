#include "gtest/gtest.h"

class Interface
{
  public:
    virtual ~Interface() = default;
    virtual int get_42() const = 0;
};

class ImplementationA : public Interface
{
  public:
    int get_42() const override final
    {
        return 42;
    }
};

class ImplementationB : public Interface
{
  public:
    int get_42() const override final
    {
        return 42;
    }
};

template<class T>
class InterfaceTest : public testing::Test   // NOTE: This is a text fixture
{
  public:
    T impl;
};

using Implementations = testing::Types<ImplementationA, ImplementationB>;
TYPED_TEST_SUITE(InterfaceTest, Implementations);

TYPED_TEST(InterfaceTest, Get42)
{
    EXPECT_EQ(this->impl.get_42(), 42);   // NOTE: Need to get by 'this->' when referring to members of the fixture class as those are templates
}
