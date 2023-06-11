#include <gtest/gtest.h>
#include "piece.h"
#include "mockArena.h"

using namespace piece;

class PieceTests : public ::testing::Test
{
public:
    MockArena mockArena;
    Piece piece;

    PieceTests() : piece(mockArena) {}
};


TEST_F(PieceTests, pieces_array_accessed_by_array_index)
{
    // Given
    pieceIndex currentPiece = p3;
    piece.setCurrentPiece(currentPiece);

    // When Then
    const wchar_t* expected = L"...."
                               ".XX."
                               ".XX."
                               "....";
    ASSERT_STREQ(piece.getPieceData(piece.getCurrentPiece()), expected);

    // Given
    currentPiece = p7;
    piece.setCurrentPiece(currentPiece);

    // When Then
    expected = L"..X...X..XX.....";
    ASSERT_STREQ(piece.getPieceData(piece.getCurrentPiece()), expected);
}


TEST_F(PieceTests, drawCurrentPiece_passes_piece_and_location_to_arena_for_drawing)
{
    // Given
    pieceIndex pieceIndex = p5;
    piece.setCurrentPiece(pieceIndex);
    int arenaX = 3, arenaY = 2;
    piece.setArenaX(arenaX);
    piece.setArenaY(arenaY);

    // When
    piece.drawCurrentPiece();

    // Then
    ASSERT_STREQ(mockArena.mPieceData, piece.getPieceData(pieceIndex));
    ASSERT_EQ(mockArena.mPieceHeight, defaultPieceHeight);
    ASSERT_EQ(mockArena.mPieceWidth, defaultPieceWidth);
    ASSERT_EQ(mockArena.mArenaX, arenaX);
    ASSERT_EQ(mockArena.mArenaY, arenaY);
}


TEST_F(PieceTests, createNewPiece_sets_next_piece_to_default_starting_position)
{
    // Given
    pieceIndex nextPiece = p1;
    piece.setNextPiece(nextPiece);

    // When
    piece.createNewPiece();

    // Then
    ASSERT_EQ(piece.getArenaX(), arena::defaultStartPositionX);
    ASSERT_EQ(piece.getArenaY(), arena::defaultStartPositionY);
}

