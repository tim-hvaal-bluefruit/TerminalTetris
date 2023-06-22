#include <gtest/gtest.h>
#include "game.h"
#include "mockPiece.h"
#include "mockArena.h"
#include "mockUserInput.h"
#include "mockScore.h"

using namespace game;

class GameTests : public ::testing::Test
{
public:
    Game game;
    MockPiece mockPiece;
    MockArena mockArena;
    MockUserInput mockUserInput;
    MockScore mockScore;

    GameTests() : game(mockPiece, mockUserInput, mockArena, mockScore) {}
};


TEST_F(GameTests, dropDown_returns_true_if_piece_can_drop)
{
    mockPiece.mIsMovePossible = true;

    // When & Then
    ASSERT_TRUE(game.dropDown());
}


TEST_F(GameTests, dropDown_returns_false_and_adds_piece_to_arena_if_piece_lands)
{
    mockPiece.mIsMovePossible = false;

    // When & Then
    ASSERT_FALSE(game.dropDown());
    ASSERT_TRUE(mockPiece.mAddPieceToArenaCalled);
}


TEST_F(GameTests, gameTick_resets_tick_count_timer_when_tick_count_equals_fall_ticks)
{
    game.setTickCount(game.getFallTicks() - 1);

    // When & Then
    game.gameTick();
    ASSERT_TRUE(mockPiece.mMoveDownCalled);
    ASSERT_EQ(game.getTickCount(), 0);
}


TEST_F(GameTests, gameTick_returns_false_when_no_space_for_new_piece) // game over
{
    // Given
    mockPiece.mIsMovePossible = false;
    mockPiece.mSpaceForNewPiece = false;
    game.setTickCount(game.getFallTicks() - 1);

    // When & Then
    ASSERT_FALSE(game.gameTick());
}

TEST_F(GameTests, gameOver_draws_game_over_to_screen)
{
    // When
    game.gameOver();

    // Then
    ASSERT_EQ(mockArena.mArenaX, textArenaPosX);
    ASSERT_EQ(mockArena.mArenaY, textArenaPosY);
}

TEST_F(GameTests, startGame_returns_true_start_button_pressed_and_false_if_not_pressed)
{
    mockUserInput.mStartGamePressed = true;
    ASSERT_TRUE(game.startGame());

    mockUserInput.mStartGamePressed = false;
    ASSERT_FALSE(game.startGame());
}
