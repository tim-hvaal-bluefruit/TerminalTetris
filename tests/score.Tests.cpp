#include <gtest/gtest.h>
#include "score.h"
#include "mockScreenBuffer.h"

using namespace score;

TEST(ScoreTests, draw_to_buffer_passes_elemnts_to_be_drawn)
{
    // Given
    MockScreenBuffer mockScreenBuffer;
    Score score(mockScreenBuffer);

    const int h = 1, w = 4;
    const int x = 5, y = 6;
    const wchar_t* element = L"2222";

    // When
    score.drawToBuffer(element, h, w, x, y);

    // Then
    ASSERT_EQ(mockScreenBuffer.mObjectHeight, h);
    ASSERT_EQ(mockScreenBuffer.mObjectWidth, w);
    ASSERT_EQ(mockScreenBuffer.mObjectXOffset, x);
    ASSERT_EQ(mockScreenBuffer.mObjectYOffset, y);
}

TEST(ScoreTests, three_score_elements_drawn_to_the_buffer)
{
    // Given
    MockScreenBuffer mockScreenBuffer;
    Score score(mockScreenBuffer);

    // When
    score.drawElementsToBuffer();

    // Then
    ASSERT_EQ(mockScreenBuffer.mCallCount, 3);
}