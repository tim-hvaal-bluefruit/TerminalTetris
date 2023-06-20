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
    ASSERT_STREQ(mockArena.mObjectData, piece.getPieceData(pieceIndex));
    ASSERT_EQ(mockArena.mObjectHeight, defaultPieceHeight);
    ASSERT_EQ(mockArena.mObjectWidth, defaultPieceWidth);
    ASSERT_EQ(mockArena.mArenaX, arenaX);
    ASSERT_EQ(mockArena.mArenaY, arenaY);
}


TEST_F(PieceTests, drawCurrentPiece_passes_current_piece_at_current_rotation_to_arena)
{
    // Given
    piece.setCurrentPiece(p2);
    piece.setCurrentRotation(r90);
    const wchar_t* expectedRotatedTeePiece =
       L"    "
        "  X "
        " XXX"
        "    ";

    // When & Then
    piece.drawCurrentPiece();
    ASSERT_STREQ(mockArena.mObjectData, expectedRotatedTeePiece);
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
    mockArena.mObjectFits = true;
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


TEST_F(PieceTests, movePiece_does_not_move_piece_if_object_does_not_fit)
{
    // Given
    mockArena.mObjectFits = false;

    // When can't move
    piece.movePiece(moveDirection::left);

    // Then not moved
    int checkPos = mockArena.mArenaX;
    ASSERT_EQ(checkPos + 1, piece.getArenaX());
    ASSERT_EQ(mockArena.mArenaY, piece.getArenaY());

    // When can't move
    piece.movePiece(moveDirection::right);

    // Then not moved
    checkPos = mockArena.mArenaX;
    ASSERT_EQ(checkPos - 1, piece.getArenaX());
    ASSERT_EQ(mockArena.mArenaY, piece.getArenaY());

    // When can't move
    piece.movePiece(moveDirection::down);

    // Then not moved
    checkPos = mockArena.mArenaY;
    ASSERT_EQ(mockArena.mArenaX, piece.getArenaX());
    ASSERT_EQ(checkPos - 1, piece.getArenaY());
}


TEST_F(PieceTests, movePiece_moves_piece_if_object_fits)
{
    // Given
    mockArena.mObjectFits = true;

    // When space left
    piece.movePiece(moveDirection::left);

    // Then moved
    int checkPos = mockArena.mArenaX;
    ASSERT_EQ(checkPos, piece.getArenaX());
    ASSERT_EQ(mockArena.mArenaY, piece.getArenaY());

    // When space right
    piece.movePiece(moveDirection::right);

    // Then moved
    checkPos = mockArena.mArenaX;
    ASSERT_EQ(checkPos, piece.getArenaX());
    ASSERT_EQ(mockArena.mArenaY, piece.getArenaY());

    // When space down
    piece.movePiece(moveDirection::down);

    // Then moved
    checkPos = mockArena.mArenaY;
    ASSERT_EQ(mockArena.mArenaX, piece.getArenaX());
    ASSERT_EQ(checkPos, piece.getArenaY());
}


TEST_F(PieceTests, movePiece_returns_true_if_object_fits)
{
    mockArena.mObjectFits = true;
    ASSERT_TRUE(piece.movePiece(moveDirection::right ));
}


TEST_F(PieceTests, movePiece_returns_false_if_object_does_not_fit)
{
    mockArena.mObjectFits = false;
    ASSERT_FALSE(piece.movePiece(moveDirection::down));
}


TEST_F(PieceTests, addPieceToArena_passes_piece_to_arena_to_update)
{
    // Given
    piece.setArenaX(10);
    piece.setArenaY(10);


    // When
    piece.addPieceToArena();

    // Then
    ASSERT_EQ(mockArena.mArenaX, piece.getArenaX());
    ASSERT_EQ(mockArena.mArenaY, piece.getArenaY());
}


TEST_F(PieceTests, addPieceToArena_passes_current_piece_at_current_rotation_to_arena)
{
    // Given
    piece.setCurrentPiece(p2);
    piece.setCurrentRotation(r90);
    const wchar_t* expectedRotatedTeePiece =
       L"    "
        "  X "
        " XXX"
        "    ";

    // When & Then
    piece.addPieceToArena();
    ASSERT_STREQ(mockArena.mObjectData, expectedRotatedTeePiece);
}


TEST_F(PieceTests, createNewPiece_returns_false_if_piece_does_not_fit)
{
    mockArena.mObjectFits = false;
    ASSERT_FALSE(piece.createNewPiece());
}


TEST_F(PieceTests, createNewPiece_returns_true_if_piece_fits)
{
    mockArena.mObjectFits = true;
    ASSERT_TRUE(piece.createNewPiece());
}


TEST_F(PieceTests, rotateIndex_returns_the_unrotated_index_if_rotation_is_0)
{
    // no rotation so expected = (y * width) + x

    // 0  1  2  3
    // 4  5  6  7
    // 8  9  10 11
    // 12 13 14 15

    // Given
    const int width = 4, height = 4;
    const rotation rotation = r0;
    int x = 0, y = 0, expectedIndex = 0; // 0*4 + 0

    // When & Then
    int rotatedIndex = piece.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);


    // Given
    x = 1; y = 0; expectedIndex = 1; // 0*4 + 1

    // When & Then
    rotatedIndex = piece.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, 1);


    // Given
    x = 3; y = 3; expectedIndex = 15; // 3*4 + 3

    // When & Then
    rotatedIndex = piece.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);
}


TEST_F(PieceTests, rotateIndex_returns_the_90_rotated_index_if_rotation_set_to_90)
{
    // 90 deg rotation so expected = ( (height - 1) * width ) + y - (x * width)

    // 12 8  4  0
    // 13 9  5  1
    // 14 10 6  2
    // 15 11 7  3

    // Given
    const int width = 4, height = 4;
    const rotation rotation = r90;
    int x = 0, y = 0, expectedIndex = 12; // (4-1)*4 + 0 - (0 * 4)

    // When & Then
    int rotatedIndex = piece.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);


    // Given
    x = 1; y = 0; expectedIndex = 8; // (4-1)*4 + 0 - (1 * 4)

    // When & Then
    rotatedIndex = piece.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);


    // Given
    x = 3; y = 3; expectedIndex = 3; // (4-1)*4 + 3 - (3 * 4)

    // When & Then
    rotatedIndex = piece.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);
}


TEST_F(PieceTests, rotateIndex_returns_the_180_rotated_index_if_rotation_set_to_180)
{
    // 180 deg rotation so expected = ( height * width - 1 ) - ( y * 4 ) - x

    // 15 14 13 12
    // 11 10 9  8
    // 7  6  5  4
    // 3  2  1  0

    // Given
    const int width = 4, height = 4;
    const rotation rotation = r180;
    int x = 0, y = 0, expectedIndex = 15; // (4*4 - 1) - ( 0 * 4) - 0

    // When & Then
    int rotatedIndex = piece.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);


    // Given
    x = 1; y = 0; expectedIndex = 14; // (4*4 - 1) - ( 0 * 4) - 1

    // When & Then
    rotatedIndex = piece.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);


    // Given
    x = 3; y = 3; expectedIndex = 0; // (4*4 - 1) - ( 3 * 4) - 3

    // When & Then
    rotatedIndex = piece.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);
}


TEST_F(PieceTests, rotateIndex_returns_the_270_rotated_index_if_rotation_set_to_270)
{
    // 270 deg rotation so expected = (width - 1) - y + ( x * height )

    // 3  7  11 15
    // 2  6  10 14
    // 1  5  9  13
    // 0  4  8  12

    // Given
    const int width = 4, height = 4;
    const rotation rotation = r270;
    int x = 0, y = 0, expectedIndex = 3; // (4-1) - 0 + (0 * 4)

    // When & Then
    int rotatedIndex = piece.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);


    // Given
    x = 1; y = 0; expectedIndex = 7; // (4-1) - 0 + (1 * 4)

    // When & Then
    rotatedIndex = piece.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);


    // Given
    x = 3; y = 3; expectedIndex = 12; // (4-1) - 3 + (3 * 4)

    // When & Then
    rotatedIndex = piece.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);
}


TEST_F(PieceTests, rotateIndex_returns_unrotated_index_in_the_default_case)
{
    // Given
    const int width = 4, height = 4;
    const rotation rotation = rotationCount;
    int x = 1, y = 0, expectedIndex = 1; // unrotated

    // When & Then
    int rotatedIndex = piece.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);
}


TEST_F(PieceTests, rotatePiece_rotates_current_piece_and_copies_to_buffer)
{
    // Given - rotate tee piece 90 degrees
    int height = defaultPieceHeight;
    int width = defaultPieceHeight;

    wchar_t pieceBuffer[height * width];
    pieceBuffer[width * height] = '\0';

    piece.setCurrentPiece(p2);
    // unrotated piece
    // "  X "
    // " XX "
    // "  X "
    // "    "

    piece.setCurrentRotation(rotation::r90);
    const wchar_t* expectedRotatedTeePiece =
       L"    "
        "  X "
        " XXX"
        "    ";

    // When & Then
    piece.rotatePiece(pieceBuffer, piece.getCurrentPiece(), piece.getCurrentRotation(), height, width);
    ASSERT_STREQ(pieceBuffer, expectedRotatedTeePiece);


    // Given - rotate long piece 270 degrees
    piece.setCurrentPiece(p1);
    // unrotated piece
    // "  X "
    // "  X "
    // "  X "
    // "  X ";

    piece.setCurrentRotation(rotation::r270);
    const wchar_t* expectedRotatedLongPiece =
       L"    "
        "XXXX"
        "    "
        "    ";

    // When & Then
    piece.rotatePiece(pieceBuffer, piece.getCurrentPiece(), piece.getCurrentRotation(), height, width);
    ASSERT_STREQ(pieceBuffer, expectedRotatedLongPiece);
}


TEST_F(PieceTests, checkPieceFits_passes_current_piece_at_current_rotation_for_arena_to_check)
{
    // Given
    const int arenaX = 10;
    const int arenaY = 10;
    piece.setCurrentPiece(p2);
    piece.setCurrentRotation(r90);
    const wchar_t* expectedRotatedTeePiece =
       L"    "
        "  X "
        " XXX"
        "    ";

    // When & Then
    piece.checkPieceFits(arenaX, arenaY);
    ASSERT_STREQ(mockArena.mObjectData, expectedRotatedTeePiece);
}
