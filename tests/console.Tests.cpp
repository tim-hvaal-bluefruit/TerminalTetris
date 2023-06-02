#include <gtest/gtest.h>
#include "console.h"
#include "mockScreenBuffer.h"

using namespace screenBuffer;

TEST(consoleTests, copy_screen_to_console__copies_buffer_to_std_out)
{
    //Given
    MockScreenBuffer mockBuffer;
    mockBuffer.fillBuffer('!');
    Console console(mockBuffer);

    testing::internal::CaptureStdout();

    //When
    console.copyScreenToConsole();

    //Then
    std::string actual = testing::internal::GetCapturedStdout();
    std::wstring wideString(mockBuffer.buffer());
    std::string expected(wideString.begin(), wideString.end());
    ASSERT_EQ(actual, expected);
}
