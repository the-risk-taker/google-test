# Google Test Notes

- [General](#general)
- [Own main()](#own-main)
- [Tracing](#tracing)
- [Writing tests](#writing-tests)
- [Writing test fixtures](#writing-test-fixtures)
- [Custom failure messages](#custom-failure-messages)
- [Parametrized tests](#parametrized-tests)
- [Typed tests](#typed-tests)
- [Matchers](#matchers)
  - [Basic Matchers](#basic-matchers)
  - [Composite Matchers](#composite-matchers)
  - [Container Matchers](#container-matchers)
  - [Example Usage](#example-usage)
- [GMock](#gmock)
  - [Stub vs Fake vs Mock](#stub-vs-fake-vs-mock)
  - [General usage](#general-usage)
  - [Writing mocks](#writing-mocks)
  - [Uninteresting calls](#uninteresting-calls)

## General

The assertions come in pairs that test the same thing but have different effects on the current function. `ASSERT_*` versions generate fatal failures when they fail, and abort the current function. `EXPECT_*` versions generate nonfatal failures, which don’t abort the current function. Usually EXPECT_*are preferred, as they allow more than one failure to be reported in a test. However, you should use ASSERT_* if it doesn’t make sense to continue when the assertion in question fails.

## Own main()

Writing own `main()` looks like this:

```c++
#include <gtest/gtest.h>


TEST(HelloTest, BasicAssertions) {
  EXPECT_EQ(7 * 6, 42);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

```

Generally, don't write own main() and don't link with `GTest::gtest`, instead don't write own main() and link to `GTest::gtest_main`.

## Tracing

When having to trace tests, there is `SCOPED_TRACE` macro:

```cpp
TEST(SubTest, WithScopeTrace) {
  {
    SCOPED_TRACE("MyScope1");

    MyFunction(1);
    {
      SCOPED_TRACE("MyScope2");
      MyFunction(1);
    }
  }
  MyFunction(1);
}
```

## Writing tests

```c++
TEST(TestSuiteName, TestName) {
  ... test body ...
}
```

## Writing test fixtures

A test fixture is a class that provides a common setup and teardown for multiple test cases that share the same initial conditions and cleanup steps. It allows to define member functions and variables that can be reused across multiple tests to avoid code duplication.

Derive test fixture class from `testing::Test`. Inside the class, declare any objects you plan to use.

Use it with:

```c++
TEST_F(TestFixtureClassName, TestName) {
  ... test body ...
}
```

## Custom failure messages

```c++
ASSERT_EQ(x.size(), y.size()) << "Vectors x and y are of unequal length";

for (int i = 0; i < x.size(); ++i) {
  EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
}
```

## Parametrized tests

Parametrized Tests: allow running same test with different parameters, reduce code duplication. Use `TEST_P` instead of `TEST`, define parameter generator with `INSTANTIATE_TEST_SUITE_P`:

```c++
class FooTest : public testing::TestWithParam<int> {};

TEST_P(FooTest, DoesXyz) {
    int value = GetParam();
    EXPECT_TRUE(Foo(value));
}

INSTANTIATE_TEST_SUITE_P(
    FooValues,
    FooTest,
    testing::Values(1, 2, 42)
);
```

## Typed tests

Typed tests: allow testing same logic with different types, useful for template code testing. Use `TYPED_TEST_SUITE` and `TYPED_TEST`.

## Matchers

Google Test provides a rich set of matchers for validating values in tests. Matchers can be used with `EXPECT_THAT` and `ASSERT_THAT` to make assertions more expressive and readable.

### Basic Matchers

- `Eq(value)`: Checks if the argument is equal to `value`.
- `Ne(value)`: Checks if the argument is not equal to `value`.
- `Lt(value)`: Checks if the argument is less than `value`.
- `Le(value)`: Checks if the argument is less than or equal to `value`.
- `Gt(value)`: Checks if the argument is greater than `value`.
- `Ge(value)`: Checks if the argument is greater than or equal to `value`.

### Composite Matchers

- `AllOf(m1, m2, ...)`: Checks if all of the matchers match.
- `AnyOf(m1, m2, ...)`: Checks if any of the matchers match.
- `Not(m)`: Checks if the matcher does not match.

### Container Matchers

- `ElementsAre(e1, e2, ...)`: Checks if the container's elements match the given matchers.
- `Contains(e)`: Checks if the container contains an element that matches the given matcher.
- `IsEmpty()`: Checks if the container is empty.

### Example Usage

```c++
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Eq;
using ::testing::Le;
using ::testing::Contains;

TEST(MatcherTest, BasicMatchers) {
  EXPECT_THAT(42, Eq(42));
  EXPECT_THAT(42, Le(100));
}

TEST(MatcherTest, ContainerMatchers) {
  std::vector<int> vec = {1, 2, 3};
  EXPECT_THAT(vec, Contains(2));
  EXPECT_THAT(vec, Not(IsEmpty()));
}
```

## GMock

GMock is a mocking framework that allows you to create mock objects for testing. A mock object implements the same interface as a real object, allowing you to specify at runtime:

- Which methods will be called
- Expected call order
- Call frequency
- Expected arguments
- Return values

### Stub vs Fake vs Mock

Mock objects differ from other test doubles:

- **Stubs**: Provide predefined responses without real logic
- **Fakes**: Have working implementations with shortcuts (e.g., in-memory database)
- **Mocks**: Verify interactions by tracking expected calls and arguments

| Type  | Purpose                   | Behavior                    |
|-------|---------------------------|-----------------------------|
| Stubs | Simulate behavior         | Return predefined responses |
| Fakes | Simplified implementation | Provide test-suitable logic |
| Mocks | Verify interactions       | Track calls and arguments   |

### General usage

`GMock` uses the `EXPECT_CALL()` or `ON_CALL()` macro to set an expectation on a mock method. The general syntax is:

```c++
EXPECT_CALL(mock_object, method_name(matchers...))
    .With(multi_argument_matcher)  // Can be used at most once
    .Times(cardinality)            // Can be used at most once
    .InSequence(sequences...)      // Can be used any number of times
    .After(expectations...)        // Can be used any number of times
    .WillOnce(action)              // Can be used any number of times
    .WillRepeatedly(action)        // Can be used at most once
    .RetiresOnSaturation();        // Can be used at most once
```

```c++
ON_CALL(mock_object, method_name(matchers...))
    .With(multi_argument_matcher)  // Can be used at most once
    .WillByDefault(action);        // Required
```

for example:

```c++
using ::testing::Return;
...
EXPECT_CALL(turtle, GetX())
    .Times(5)
    .WillOnce(Return(100))
    .WillOnce(Return(150))
    .WillRepeatedly(Return(200));
```

says that the turtle object's GetX() method will be called five times, it will return 100 the first time, 150 the second time, and then 200 every time. Some people like to call this style of syntax a Domain-Specific Language (DSL).

> [!TIP]  
> Use `ON_CALL()` if you just want to specify what should happen when the mocked function is called. Use `EXPECT_CALL()` if you want also check if and how the mocked functions is being called. Use EXPECT_CALL() only if you have to.

```c++
ON_CALL(mock_server, GetBalance(account_number))
    .WillByDefault(Return(2000));

// vs

EXPECT_THAT(mock_server, GetBalance(account_number))
    .Times(AtLeast(1))
    .WillRepeatedly(Return(2000));
```

### Writing mocks

Inherit from `base` class and wrap methods with `MOCK_METHOD`:

```c++
MOCK_METHOD(ReturnType, MethodName, (Args...));
MOCK_METHOD(ReturnType, MethodName, (Args...), (Specs...));
```

`Specs` can be: `const`, `override`, `noexcept`.

### Uninteresting calls

GMock will warn if some mock method was called without expectations, so if warning are supposed to be suppressed, the `NiceMock<T>` can be used.

```c++
NiceMock<MyMock> mock;
```

If you want to make fails on uninteresting calls use `StrictMock<T>`:

```c++
StrictMock<MyMock> mock;
```
