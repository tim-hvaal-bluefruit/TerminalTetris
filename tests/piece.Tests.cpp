#include <gtest/gtest.h>
#include "piece.h"
#include "mockArena.h"
#include "mockScreenBuffer.h"

using namespace piece;

class PieceTests : public ::testing::Test
{
public:
    MockArena mockArena;
    MockScreenBuffer mockScreenBuffer;
    Piece piece;

    PieceTests() : piece(mockArena, mockScreenBuffer) {}
};


TEST_F(PieceTests, pieces_array_accessed_by_array_index)
{
    // Given
    pieceIndex currentPiece = p3;
    piece.setCurrentPiece(currentPiece);

    // When Then
    const wchar_t* expected = L"    "
                               " XX "
                               " XX "
                               "    ";
    ASSERT_STREQ(piece.getPieceData(piece.getCurrentPiece()), expected);

    // Given
    currentPiece = p7;
    piece.setCurrentPiece(currentPiece);

    // When Then
    expected = L"  X   X  XX     ";
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


TEST_F(PieceTests, createNewPiece_sets_preview_piece_to_new_piece_in_default_start_position)
{
    // Given
    pieceIndex previewPiece = p1;
    piece.setPreviewPiece(previewPiece);

    // When
    piece.createNewPiece();

    // Then
    ASSERT_EQ(piece.getArenaX(), arena::defaultStartPositionX);
    ASSERT_EQ(piece.getArenaY(), arena::defaultStartPositionY);
}


TEST_F(PieceTests, createNewPiece_generates_a_new_random_preview_piece)
{
    // Given
    pieceIndex oldPreviewPiece = p3;
    piece.setPreviewPiece(oldPreviewPiece);

    // When
    piece.createNewPiece();

    // Then
    pieceIndex newPreviewPiece = piece.getPreviewPiece();
    ASSERT_TRUE(newPreviewPiece >= 0 && newPreviewPiece <= 6); // not testing randomness here, but check it's valid
}


TEST_F(PieceTests, movePiece_moves_piece_one_to_the_left_right_or_down)
{
    // Given
    pieceIndex previewPiece = p1;
    piece.setPreviewPiece(previewPiece);
    piece.createNewPiece();
    int currentArenaX = piece.getArenaX();
    int currentArenaY = piece.getArenaY();

    // When & Then
    piece.movePiece(moveDirection::left);
    ASSERT_EQ(piece.getArenaX(), currentArenaX - 1);

    // When & Then
    piece.movePiece(moveDirection::right);
    ASSERT_EQ(piece.getArenaX(), currentArenaX);

    // When & Then
    piece.movePiece(moveDirection::down);
    ASSERT_EQ(piece.getArenaY(), currentArenaY + 1);
}


TEST_F(PieceTests, drawPreviewPiece_draws_preview_piece_directly_to_screen_buffer)
{
    // Given
    const int expectedSize = defaultPieceHeight * defaultPieceWidth;

    // When
    piece.drawPreviewPiece();

    // Then
    ASSERT_EQ(mockScreenBuffer.mObjectSize, expectedSize);
}
