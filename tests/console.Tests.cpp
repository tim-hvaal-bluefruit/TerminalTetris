#include <gtest/gtest.h>
#include "console.h"


TEST(consoleTests, draw_to_console__draws_buffer_to_std_out)
{
    //Given
    Console console;
    wchar_t screenBuffer[screenBufferSize];
    for (size_t i = 0; i < screenBufferSize; i++)
        screenBuffer[i] = '!';
    testing::internal::CaptureStdout();

    //When
    console.drawToConsole(screenBuffer);

    //Then
    std::string actual = testing::internal::GetCapturedStdout();
    std::wstring ws(screenBuffer);
    std::string expected(ws.begin(), ws.end());
    ASSERT_EQ(actual, expected);
}
