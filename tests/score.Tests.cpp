#include <gtest/gtest.h>
#include "score.h"
#include "mockScreenBuffer.h"
#include "observerInterface.h"

using namespace score;
using namespace observer;
using namespace screen;

class ScoreTests : public ::testing::Test
{
public:
    ScoreTests() : score(mockScreenBuffer) {}

    MockScreenBuffer mockScreenBuffer;
    Score score;
};


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


TEST_F(ScoreTests, score_can_subscribe_to_a_subject)
{
    Subject mockSubject;
    mockSubject.addObserver(&score, Event::linesCompleted);
    ASSERT_EQ(mockSubject.getObservers()->entity, &score);
}


TEST_F(ScoreTests, onNotify_does_not_update_score_on_irrelevant_event_from_subject)
{
    // Given
    int initialScore = score.getScore();

    Subject mockSubject;
    mockSubject.addObserver(&score, Event::linesCompleted);

    Event irrelevantEvent = Event::gameOver;
    int irrelevantValue = 1;

    // When
    mockSubject.notify(irrelevantEvent, irrelevantValue);

    // Then
    ASSERT_EQ(score.getScore(), initialScore);
}


TEST_F(ScoreTests, onNotify_updates_score_on_event_depending_on_number_of_lines_completed)
{
    // Given
    Subject mockSubject;
    mockSubject.addObserver(&score, Event::linesCompleted);

    int initialScore = score.getScore();
    int linesCompleted = 1;

    // When & Then
    mockSubject.notify(Event::linesCompleted, linesCompleted);
    ASSERT_EQ(score.getScore(), initialScore + oneLinePoints);


    // Given
    linesCompleted = 2;

    // When & Then
    mockSubject.notify(Event::linesCompleted, linesCompleted);
    ASSERT_EQ(score.getScore(), initialScore + oneLinePoints + twoLinePoints);


    // Given
    linesCompleted = 3;

    // When & Then
    mockSubject.notify(Event::linesCompleted, linesCompleted);
    ASSERT_EQ(score.getScore(), initialScore + oneLinePoints + twoLinePoints + threeLinePoints);


    // Given
    linesCompleted = 4;

    // When & Then
    mockSubject.notify(Event::linesCompleted, linesCompleted);
    ASSERT_EQ(score.getScore(), initialScore + oneLinePoints + twoLinePoints + threeLinePoints + fourLinePoints);
}


TEST_F(ScoreTests, onNotify_resets_score_on_game_over_event)
{
    // Given
    Subject mockSubject;
    mockSubject.addObserver(&score, Event::gameOver);

    score.updateScore(1);
    int gameOver = 0;

    // When & Then
    mockSubject.notify(Event::gameOver, gameOver);
    ASSERT_EQ(score.getScore(), 0);
}


TEST_F(ScoreTests, on_construction_score_registers_as_draw_item_with_screen_buffer)
{
    ASSERT_EQ(mockScreenBuffer.mNumRegisteredDrawItems, 1);
}


TEST_F(ScoreTests, draw_draws_three_elements_to_screen_buffer)
{
    // Given
    ASSERT_EQ(mockScreenBuffer.mCallCount, 0);

    // When Then
    score.draw();
    ASSERT_EQ(mockScreenBuffer.mCallCount, 3);
}
