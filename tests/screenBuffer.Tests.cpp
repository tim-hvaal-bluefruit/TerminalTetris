#include <gtest/gtest.h>
#include "screenBuffer.h"

using namespace screen;


TEST(ScreenBufferTests, default_constructor_sets_buffer_size_to_default_size)
{
    // When
    ScreenBuffer screenBuffer;

    // Then
    std::wstring expectedBuffer(screenBuffer.buffer());
    ASSERT_EQ(defaultScreenHeight * defaultScreenWidth, expectedBuffer.size());
}


TEST(ScreenBufferTests, overriden_constructor_sets_buffer_size_to_given_dimensions)
{
    // When
    const int height = 10, width = 20;
    const int expectedSize = height * width;
    ScreenBuffer screenBuffer(height, width);

    // Then
    std::wstring expectedBuffer(screenBuffer.buffer());
    ASSERT_EQ(expectedSize, expectedBuffer.size());
}


TEST(ScreenBufferTests, fillBuffer_fills_available_buffer)
{
    // Given
    ScreenBuffer screenBuffer;
    wchar_t fillChar = L'Q';
    std::wstring expectedBuffer((defaultScreenHeight * defaultScreenWidth), fillChar);

    // When
    screenBuffer.fillBuffer(fillChar);

    // Then
    std::wstring actualBuffer(screenBuffer.buffer());
    ASSERT_EQ(actualBuffer, expectedBuffer);
}


TEST(ScreenBufferTests, setScreenBuffer_resets_to_given_dimensions)
{
    // Given
    ScreenBuffer screenBuffer;
    std::wstring startBuffer(screenBuffer.buffer());
    EXPECT_EQ(defaultScreenHeight * defaultScreenWidth, startBuffer.size());

    const int height = 10, width = 5;
    const int expectedSize = height * width;

    // // When
    screenBuffer.setScreenBufferSize(height, width);

    // Then
    std::wstring actualBuffer = screenBuffer.buffer();
    ASSERT_EQ(expectedSize, actualBuffer.size());
}


TEST(ScreenBufferTests, drawToBuffer_draws_an_object_to_the_screen_buffer)
{
    // Given
    const int height = 4, width = 4;
    ScreenBuffer screenBuffer(height, width);

    const int objectHeight = 3, objectWidth = 3;
    const char* object = "#.#"
                         "#.#"
                         "###";

    // When
    screenBuffer.drawToBuffer(object, objectHeight, objectWidth);

    // Then
    const wchar_t * expectedBuffer = L"#.#."
                                      "#.#."
                                      "###."
                                      "....";
    ASSERT_STREQ(expectedBuffer, screenBuffer.buffer());
}
