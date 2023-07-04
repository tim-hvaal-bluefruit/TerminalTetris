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
    // Given
    mMockPiece.mIsMovePossible = true;

    // When Then
    ASSERT_TRUE(mGame.dropDown());
}


TEST_F(GameTests, dropDown_returns_false_and_adds_piece_to_arena_if_piece_lands)
{
    // Given
    mMockPiece.mIsMovePossible = false;

    // When Then
    ASSERT_FALSE(mGame.dropDown());
    ASSERT_TRUE(mMockPiece.mAddPieceToArenaCalled);
}


TEST_F(GameTests, gameRunning_resets_tick_count_timer_when_tick_count_equals_fall_ticks)
{
    // Given
    mGame.tickCount = mGame.fallTicks - 1;

    // When Then
    mGame.gameInProgress();
    ASSERT_TRUE(mMockPiece.mMoveDownCalled);
    ASSERT_EQ(mGame.tickCount, 0);
}


TEST_F(GameTests, gameOver_draws_game_over_to_screen)
{
    // When
    mGame.gameOver();

    // Then
    ASSERT_EQ(mMockArena.mArenaX, textArenaPosX);
    ASSERT_EQ(mMockArena.mArenaY, textArenaPosY);
}

TEST_F(GameTests, score_string_refreshed_when_game_starts)
{
    // Given
    mGame.menuScreen();
    mMockUserInput.getUserInput();
    ASSERT_EQ(mMockScore.callCount, 0);

    // When
    mMockUserInput.mStartGamePressed = true;
    ASSERT_FALSE(mGame.menuScreen());

    // Then
    ASSERT_EQ(mMockScore.callCount, 1);
}




TEST_F(GameTests, game_starts_on_menu_screen)
{
    // Given
    ASSERT_EQ(mGame.gameState, Game::GameState::MenuScreen);

    // When Then
    mGame.gameTick();
    ASSERT_EQ(mGame.gameState, Game::GameState::MenuScreen);
}


TEST_F(GameTests, pressing_start_button_plays_game)
{
    // Given
    ASSERT_EQ(mGame.gameState, Game::GameState::MenuScreen);
    mMockUserInput.mStartGamePressed = true;

    // When Then
    mGame.gameTick();
    ASSERT_EQ(mGame.gameState, Game::GameState::GameInProgress);
}


TEST_F(GameTests, game_over_when_game_no_longer_in_progress)
{
    // Given
    mGame.gameState = Game::GameState::GameInProgress;
    mMockPiece.mIsMovePossible = false;
    mMockPiece.mSpaceForNewPiece = false;
    mGame.tickCount = mGame.fallTicks - 1;

    // When Then
    mGame.gameTick();
    ASSERT_EQ(mGame.gameState, Game::GameState::GameOver);
}


TEST_F(GameTests, pause_on_game_over_screen_until_tick_timer_reaches_restart_threshold)
{
    // Given
    mGame.gameState = Game::GameState::GameOver;
    mGame.stackBurned = true;
    mGame.tickCount = restartGameTicks - 1;

    // When Then
    mGame.gameTick();
    ASSERT_EQ(mGame.gameState, Game::GameState::GameOver);

    // Given When Then
    mGame.tickCount = restartGameTicks;
    mGame.gameTick();
    ASSERT_EQ(mGame.gameState, Game::GameState::MenuScreen);
}


// TODO 
// game tick returns true while game running
// game tick returns false when user quits (however they do that)
// add test in application to make sure outer loop quits to main
