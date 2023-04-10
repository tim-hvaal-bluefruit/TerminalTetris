add_executable(
    AllTests
    allTests.Tests.cpp
    ../src/print.cpp
)

target_link_libraries(
    AllTests
    GTest::gtest_main
)