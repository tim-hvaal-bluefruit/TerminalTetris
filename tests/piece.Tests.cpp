#include <gtest/gtest.h>
#include "piece.h"

using namespace piece;

TEST(PieceTests, pieces_array_accessed_by_array_index)
{
    // Given
    Piece piece;
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
