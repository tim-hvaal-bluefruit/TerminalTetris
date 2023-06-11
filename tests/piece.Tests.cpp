#include <gtest/gtest.h>
#include "piece.h"
#include "mockArena.h"

using namespace piece;

TEST(PieceTests, pieces_array_accessed_by_array_index)
{
    // Given
    MockArena mockArena;
    Piece piece(mockArena);
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

TEST(PieceTests, drawCurrentPiece_passes_piece_and_location_to_arena_for_drawing)
{
    // Given
    MockArena mockArena;
    Piece piece(mockArena);

    pieceIndex pieceIndex = p5;
    piece.setCurrentPiece(pieceIndex);
    int arenaX = 3, arenaY = 2;

    // When
    piece.drawCurrentPiece(arenaX, arenaY);

    // Then
    ASSERT_STREQ(mockArena.mPieceData, piece.getPieceData(pieceIndex));
    ASSERT_EQ(mockArena.mPieceHeight, defaultPieceHeight);
    ASSERT_EQ(mockArena.mPieceWidth, defaultPieceWidth);
    ASSERT_EQ(mockArena.mArenaX, arenaX);
    ASSERT_EQ(mockArena.mArenaY, arenaY);
}