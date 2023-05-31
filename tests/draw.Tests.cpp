#include <gtest/gtest.h>
#include <string>
#include "print.h"
#include "draw.h"


TEST(drawTests, print_prints_input)
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


TEST(drawTests, draw_draws_playing_field)
{
    //Given
    testing::internal::CaptureStdout();
    std::string field = "........";

    //When
    draw(field);

    //Then
    std::string actual = testing::internal::GetCapturedStdout();
    ASSERT_EQ(field + "\n", actual);
}
