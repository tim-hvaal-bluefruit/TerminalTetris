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


TEST(ScreenBufferTests, drawToBuffer_draws_object_to_screen_buffer)
{
    // Given
    const int height = 4, width = 4;
    ScreenBuffer screenBuffer(height, width);

    const int objectHeight = 3, objectWidth = 3, xOffset = 0, yOffset = 0;
    const wchar_t* object = L"#.#"
                             "#.#"
                             "###";

    // When
    screenBuffer.drawToBuffer(object, objectHeight, objectWidth, xOffset, yOffset);

    // Then
    const wchar_t * expectedBuffer = L"#.#."
                                      "#.#."
                                      "###."
                                      "....";
    ASSERT_STREQ(expectedBuffer, screenBuffer.buffer());
}


TEST(ScreenBufferTests, drawToBuffer_draws_object_to_screen_buffer_at_offset_position)
{
    // Given
    const int height = 7, width = 9;
    ScreenBuffer screenBuffer(height, width);

    const int objectHeight = 3, objectWidth = 3, xOffset = 3, yOffset = 2;
    const wchar_t* object = L"#.#"
                             "#.#"
                             "###";

    // When
    screenBuffer.drawToBuffer(object, objectHeight, objectWidth, xOffset, yOffset);

    // Then
    const wchar_t * expectedBuffer = L"........."
                                      "........."
                                      "...#.#..."
                                      "...#.#..."
                                      "...###..."
                                      "........."
                                      ".........";
    ASSERT_STREQ(expectedBuffer, screenBuffer.buffer());
}


TEST(ScreenBufferTests, drawing_multiple_objects_to_screen_buffer)
{
    // Given
    const int height = 6, width = 12;
    ScreenBuffer screenBuffer(height, width);

    // When
    int objectHeight = 3, objectWidth = 4, xOffset = 1, yOffset = 1;
    const wchar_t object1[] = L"#..#"
                              "#..#"
                              "####";

    screenBuffer.drawToBuffer(object1, objectHeight, objectWidth, xOffset, yOffset);

    objectHeight = 1,
    objectWidth = 5,
    xOffset = 6,
    yOffset = 1;
    const wchar_t object2[] = L"SCORE";
    screenBuffer.drawToBuffer(object2, objectHeight, objectWidth, xOffset, yOffset);

    objectHeight = 1,
    objectWidth = 3,
    xOffset = 7,
    yOffset = 2;
    const wchar_t object3[] = L"123";
    screenBuffer.drawToBuffer(object3, objectHeight, objectWidth, xOffset, yOffset);

    // Then
    const wchar_t * expectedBuffer = L"............"
                                      ".#..#.SCORE."
                                      ".#..#..123.."
                                      ".####......."
                                      "............"
                                      "............";
    ASSERT_STREQ(expectedBuffer, screenBuffer.buffer());
}
