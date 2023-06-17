#include <gtest/gtest.h>
#include "game.h"
#include "mockPiece.h"

using namespace game;

class GameTests : public ::testing::Test
{
public:
    Game game;
    MockPiece mockPiece;

    GameTests() : game(mockPiece) {}
};

TEST_F(GameTests, fall_resets_tick_count_timer_if_move_possible)
{
    // Given
    mockPiece.mIsMovePossible = true;
    game.incrementTickCount();
    ASSERT_EQ(game.getTickCount(), 1);

    // When
    game.fall();

    // Then
    ASSERT_TRUE(mockPiece.mMoveDownCalled);
    ASSERT_EQ(game.getTickCount(), 0);
}

TEST_F(GameTests, fall_does_not_reset_tick_count_timer_if_move_impossible)
{
    // Given
    mockPiece.mIsMovePossible = false;
    game.incrementTickCount();
    ASSERT_EQ(game.getTickCount(), 1);

    // When
    game.fall();

    // Then
    ASSERT_TRUE(mockPiece.mMoveDownCalled);
    ASSERT_EQ(game.getTickCount(), 1);
}

TEST_F(GameTests, fall_adds_piece_to_arena_if_move_not_possible)
{
    // Given
    mockPiece.mIsMovePossible = false;

    // When
    game.fall();

    // Then
    ASSERT_TRUE(mockPiece.mAddPieceToArenaCalled);
}
