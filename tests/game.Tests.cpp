#include <gtest/gtest.h>
#include "game.h"
#include "mockPiece.h"
#include "mockArena.h"
#include "mockUserInput.h"
#include "mockScore.h"

using namespace game;


class GameTestObject : public Game
{
  public:
    GameTestObject(PieceInterface& piece, UserInputInterface& userInput, ArenaInterface& arena, ScoreInterface& score) :
        Game(piece, userInput, arena, score)
    {}

    GameState& gameState = mGameState;
    int& tickCount = mTickCount;
    int& fallTicks = mFallTicks;
    bool& stackBurned = mStackBurned;
};


class GameTests : public ::testing::Test
{
  public:
    GameTests() : mGame(mMockPiece, mMockUserInput, mMockArena, mMockScore) {}

    GameTestObject mGame;
    MockPiece mMockPiece;
    MockUserInput mMockUserInput;
    MockArena mMockArena;
    MockScore mMockScore;
};


TEST_F(GameTests, dropDown_returns_true_if_piece_can_drop)
{
    mMockPiece.mIsMovePossible = true;

    // When Then
    ASSERT_TRUE(mGame.dropDown());
}


TEST_F(GameTests, dropDown_returns_false_and_adds_piece_to_arena_if_piece_lands)
{
    mMockPiece.mIsMovePossible = false;

    // When Then
    ASSERT_FALSE(mGame.dropDown());
    ASSERT_TRUE(mMockPiece.mAddPieceToArenaCalled);
}


TEST_F(GameTests, gameTick_resets_tick_count_timer_when_tick_count_equals_fall_ticks)
{
    mGame.tickCount = mGame.fallTicks - 1;

    // When Then
    mGame.gameTick();
    ASSERT_TRUE(mMockPiece.mMoveDownCalled);
    ASSERT_EQ(mGame.tickCount, 0);
}


TEST_F(GameTests, gameTick_returns_false_when_no_space_for_new_piece) // game over
{
    // Given
    mMockPiece.mIsMovePossible = false;
    mMockPiece.mSpaceForNewPiece = false;
    mGame.tickCount = mGame.fallTicks - 1;

    // When & Then
    ASSERT_FALSE(mGame.gameTick());
}


TEST_F(GameTests, gameOver_draws_game_over_to_screen)
{
    // When
    mGame.gameOver();

    // Then
    ASSERT_EQ(mMockArena.mArenaX, textArenaPosX);
    ASSERT_EQ(mMockArena.mArenaY, textArenaPosY);
}


TEST_F(GameTests, startGame_returns_true_start_button_pressed_and_false_if_not_pressed)
{
    mMockUserInput.mStartGamePressed = true;
    ASSERT_TRUE(mGame.startGame());

    mMockUserInput.mStartGamePressed = false;
    ASSERT_FALSE(mGame.startGame());
}


TEST_F(GameTests, gameOver_returns_true_when_tickCount_is_less_than_newGameTicks)
{
    mGame.stackBurned = true;
    mGame.tickCount = defaultNewGameTicks - 1;
    ASSERT_TRUE(mGame.gameOver());
}


TEST_F(GameTests, gameOver_returns_false_when_tickCount_is_equal_to_newGameTicks)
{
    mGame.stackBurned = true;
    mGame.tickCount = defaultNewGameTicks;
    ASSERT_FALSE(mGame.gameOver());
}


TEST_F(GameTests, score_string_refreshed_when_game_starts)
{
    // Given
    mGame.startGame();
    mMockUserInput.getUserInput();
    ASSERT_EQ(mMockScore.callCount, 0);

    // When
    mMockUserInput.mStartGamePressed = true;
    ASSERT_TRUE(mGame.startGame());

    // Then
    ASSERT_EQ(mMockScore.callCount, 1);
}


// TEST_F(GameTests, game_starts_on_menu_screen)
// {
//     // Given
    
//     // When
//     mGame.gameloop();

//     // Then
//     ASSERT_EQ()
// }
