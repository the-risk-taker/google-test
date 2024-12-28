// NOTE: Taken from: https://github.com/ourarash/cpp-template

#include <gmock/gmock.h>

using ::testing::Field;
using ::testing::Ge;
using ::testing::Property;

class MyClass1
{
  public:
    MyClass1(int m) : m_(m) {}

    int m_;
};

TEST(MatchersTest, MemberMatchers_Field_Simple)
{
    MyClass1 my_object(1);
    EXPECT_THAT(my_object, Field(&MyClass1::m_, Ge(0)));
    EXPECT_THAT(my_object.m_, Ge(0));
}

TEST(MatchersTest, MemberMatchers_Field_Container)
{
    std::vector<MyClass1> my_objects = {MyClass1(1), MyClass1(2), MyClass1(3)};

    EXPECT_THAT(my_objects, Each(Field(&MyClass1::m_, Ge(0))));
    EXPECT_THAT(my_objects,
                UnorderedElementsAre(   //
                    Field(&MyClass1::m_, 1),
                    Field(&MyClass1::m_, 3),
                    Field(&MyClass1::m_, 2)));
}

class MyClass2
{
  public:
    MyClass2(int m) : m_(m) {}

    int GetM() const
    {
        return m_;
    }
    void SetM(int new_m)
    {
        m_ = new_m;
    }

  private:
    int m_;
};

TEST(MatchersTest, MemberMatchers_Property_Simple)
{
    MyClass2 my_object(1);
    EXPECT_THAT(my_object, Property(&MyClass2::GetM, Ge(0)));
    EXPECT_THAT(my_object.GetM(), Ge(0));
}

TEST(MatchersTest, MemberMatchers_Property_Container)
{
    std::vector<MyClass2> my_objects = {MyClass2(1), MyClass2(2), MyClass2(3)};

    EXPECT_THAT(my_objects, Each(Property(&MyClass2::GetM, Ge(0))));   // NOTE: Property only takes const methods with no arguments
    EXPECT_THAT(my_objects,
                UnorderedElementsAre(   //
                    Property(&MyClass2::GetM, 1),
                    Property(&MyClass2::GetM, 3),
                    Property(&MyClass2::GetM, 2)));
}
