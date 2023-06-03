#include <gtest/gtest.h>
#include "screenBuffer.h"

using namespace screenBuffer;

TEST(screenBufferTests, fillBuffer_fills_available_buffer)
{
    // Given
    ScreenBuffer screenBuffer;
    wchar_t fillChar = L'Q';
    std::wstring expected((screenWidth * screenHeight) -1, fillChar); // last element null terminated

    // When
    screenBuffer.fillBuffer(fillChar);

    // Then
    std::wstring actual(screenBuffer.buffer());
    ASSERT_EQ(actual, expected) << "actual:" << actual.size() << ". expected: " << expected.size();
}
