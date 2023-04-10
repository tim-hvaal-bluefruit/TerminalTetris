#include <gtest/gtest.h>
#include <string>
#include "../src/print.h"


TEST(TetrisTests, print_prints_input)
{
    //Given
    testing::internal::CaptureStdout();
    std::string input = "test input";

    //When
    print(input);

    //Then
    const std::string actual = testing::internal::GetCapturedStdout();
    ASSERT_EQ(input + "\n", actual);
}
