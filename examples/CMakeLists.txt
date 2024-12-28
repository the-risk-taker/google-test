include(GoogleTest)

function(make_test NAME DIRECTORY LIBRARY)
    add_executable(${NAME} ${DIRECTORY}/${NAME}.cpp)
    target_link_libraries(${NAME} ${LIBRARY})
    gtest_discover_tests(${NAME})
endfunction()

# own main
make_test(own_main testing GTest::gtest)

# testing with GTest
make_test(simple testing GTest::gtest_main)
make_test(test_fixture testing GTest::gtest_main)
make_test(parametrized_test testing GTest::gtest_main)
make_test(parametrized_test_with_name_generator testing GTest::gtest_main)
make_test(typed_test testing GTest::gtest_main)

# matchers
make_test(matcher_basic matchers gmock_main)
make_test(matcher_custom matchers gmock_main)
make_test(matcher_member_and_property matchers gmock_main)
make_test(matcher_truly matchers gmock_main)

# mocking with GMock
make_test(turtle mocking gmock_main)
make_test(on_call_with_fixture mocking gmock_main)
