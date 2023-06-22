#include <gtest/gtest.h>
#include "score.h"
#include "mockScreenBuffer.h"

using namespace score;

class ScoreTests : public ::testing::Test
{
public:
    ScoreTests() : score(mockScreenBuffer) {}

    MockScreenBuffer mockScreenBuffer;
    Score score;
};


TEST_F(ScoreTests, draw_to_buffer_passes_elemnts_to_be_drawn)
{
    // Given
    const int h = 1, w = 4, x = 5, y = 6;
    const wchar_t* element = L"2222";

    // When
    score.drawToBuffer(element, h, w, x, y);

    // Then
    ASSERT_EQ(mockScreenBuffer.mObjectHeight, h);
    ASSERT_EQ(mockScreenBuffer.mObjectWidth, w);
    ASSERT_EQ(mockScreenBuffer.mObjectXOffset, x);
    ASSERT_EQ(mockScreenBuffer.mObjectYOffset, y);
}


TEST_F(ScoreTests, three_score_elements_drawn_to_the_buffer)
{
    score.drawElementsToBuffer();
    ASSERT_EQ(mockScreenBuffer.mCallCount, 3);
}


TEST_F(ScoreTests, updateScore_adds_an_increment)
{
    // Given
    const int startingScore = score.getScore();
    const int lineScore = 10;

    // When & Then
    score.updateScore(lineScore);
    ASSERT_EQ(score.getScore(), lineScore + startingScore);
}


TEST_F(ScoreTests, updateScore_sets_the_score_to_the_buffer)
{
    // Given
    const int scoreOne = 99999;

    // When & Then
    score.updateScore(scoreOne);
    ASSERT_STREQ(score.getScoreBuffer(), L"99999");

    // Given
    score.setScore(0);
    const int scoreTwo = 1;

    // When & Then
    score.updateScore(scoreTwo);
    ASSERT_STREQ(score.getScoreBuffer(), L"1");
}

