#include <gmock/gmock.h>

// NOTE: The interface which will be mocked
class ITurtle
{
  public:
    virtual ~ITurtle() {}
    virtual void PenUp() = 0;
    virtual void PenDown() = 0;
    virtual void Forward(int distance) = 0;
    virtual void Turn(int degrees) = 0;
    virtual void GoTo(int x, int y) = 0;
    virtual int GetX() const = 0;
    virtual int GetY() const = 0;
};

// NOTE: The mock class
class MockTurtle : public ITurtle
{
  public:
    MOCK_METHOD(void, PenUp, (), (override));
    MOCK_METHOD(void, PenDown, (), (override));
    MOCK_METHOD(void, Forward, (int distance), (override));
    MOCK_METHOD(void, Turn, (int degrees), (override));
    MOCK_METHOD(void, GoTo, (int x, int y), (override));
    MOCK_METHOD(int, GetX, (), (const, override));
    MOCK_METHOD(int, GetY, (), (const, override));
};

using ::testing::AtLeast;

class Painter
{
    ITurtle* turtle;

  public:
    Painter(ITurtle* turtle) : turtle(turtle) {}

    bool DrawCircle(int, int, int)
    {
        turtle->PenDown();
        return true;
    }
};

TEST(PainterTest, CanDrawSomething)
{
    MockTurtle turtle;
    EXPECT_CALL(turtle, PenDown())   //
        .Times(AtLeast(1));

    Painter painter(&turtle);

    EXPECT_TRUE(painter.DrawCircle(0, 0, 10));
}
