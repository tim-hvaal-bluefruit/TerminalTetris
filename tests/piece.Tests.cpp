// #include <gtest/gtest.h>
// #include <array>
// #include "piece.h"
// #include "tetromino.h"
// #include "mockArena.h"
// #include "mockScreenBuffer.h"


// TEST_F(PieceTests, pieces_array_accessed_by_array_index)
// {
//     // Given
//     TetrominoType currentPiece = t3;
//     piece.setCurrentPiece(currentPiece);
//
//     // When Then
//     const wchar_t* expected = L"    "
//                                " XX "
//                                " XX "
//                                "    ";
//     ASSERT_STREQ(piece.getPieceData(piece.getCurrentPiece()), expected);
//
//     // Given
//     currentPiece = t7;
//     piece.setCurrentPiece(currentPiece);
//
//     // When Then
//     expected = L"  X "
//                 "  X "
//                 " XX "
//                 "    ";
//     ASSERT_STREQ(piece.getPieceData(piece.getCurrentPiece()), expected);
// }


// TEST_F(PieceTests, drawCurrentPiece_passes_piece_and_location_to_arena_for_drawing)
// {
//     // Given
//     TetrominoType tetromino = t5;
//     piece.setCurrentPiece(tetromino);
//     int arenaX = 3, arenaY = 2;
//     piece.setArenaX(arenaX);
//     piece.setArenaY(arenaY);
//
//     // When
//     piece.drawCurrentPiece();
//
//     // Then
//     ASSERT_STREQ(mockArena.mObjectData, piece.getPieceData(tetromino));
//     ASSERT_EQ(mockArena.mObjectHeight, TetrominoHeight);
//     ASSERT_EQ(mockArena.mObjectWidth, TetrominoWidth);
//     ASSERT_EQ(mockArena.mArenaX, arenaX);
//     ASSERT_EQ(mockArena.mArenaY, arenaY);
// }


// TEST_F(PieceTests, drawCurrentPiece_passes_current_piece_at_current_rotation_to_arena)
// {
//     // Given
//     piece.setCurrentPiece(t2);
//     piece.setCurrentRotation(r90);
//     const wchar_t* expectedRotatedTeePiece =
//        L"    "
//         "  X "
//         " XXX"
//         "    ";
//
//     // When & Then
//     piece.drawCurrentPiece();
//     ASSERT_STREQ(mockArena.mObjectData, expectedRotatedTeePiece);
// }


// TEST_F(PieceTests, createNewPiece_sets_preview_piece_to_new_piece_in_default_start_position)
// {
//     // Given
//     TetrominoType previewPiece = t1;
//     piece.setPreviewPiece(previewPiece);
//
//     // When
//     piece.createNewPiece();
//
//     // Then
//     ASSERT_EQ(piece.getArenaX(), arena::TetrominoStartPositionX);
//     ASSERT_EQ(piece.getArenaY(), arena::TetrominoStartPositionY);
// }


// TEST_F(PieceTests, createNewPiece_generates_a_new_random_preview_piece)
// {
//     // Given
//     TetrominoType oldPreviewPiece = t3;
//     piece.setPreviewPiece(oldPreviewPiece);
//
//     // When
//     piece.createNewPiece();
//
//     // Then
//     TetrominoType newPreviewPiece = piece.getPreviewPiece();
//     ASSERT_TRUE(newPreviewPiece >= 0 && newPreviewPiece <= 6); // not testing randomness here, but check it's valid
// }


// TEST_F(PieceTests, movePiece_moves_piece_one_to_the_left_right_or_down)
// {
//     // Given
//     mockArena.mObjectFits = true;
//     TetrominoType previewPiece = t1;
//     piece.setPreviewPiece(previewPiece);
//     piece.createNewPiece();
//     int currentArenaX = piece.getArenaX();
//     int currentArenaY = piece.getArenaY();
//
//     // When & Then
//     piece.movePiece(moveDirection::left);
//     ASSERT_EQ(piece.getArenaX(), currentArenaX - 1);
//
//     // When & Then
//     piece.movePiece(moveDirection::right);
//     ASSERT_EQ(piece.getArenaX(), currentArenaX);
//
//     // When & Then
//     piece.movePiece(moveDirection::down);
//     ASSERT_EQ(piece.getArenaY(), currentArenaY + 1);
// }


// TEST_F(PieceTests, drawPreviewPiece_draws_preview_piece_directly_to_screen_buffer)
// {
//     // Given
//     const int expectedSize = TetrominoHeight * TetrominoWidth;
//
//     // When
//     piece.drawPreviewPiece();
//
//     // Then
//     ASSERT_EQ(mockScreenBuffer.mObjectSize, expectedSize);
// }


// TEST_F(PieceTests, movePiece_does_not_move_piece_if_object_does_not_fit)
// {
//     // Given
//     mockArena.mObjectFits = false;
//
//     // When can't move
//     piece.movePiece(moveDirection::left);
//
//     // Then not moved
//     int checkPos = mockArena.mArenaX;
//     ASSERT_EQ(checkPos + 1, piece.getArenaX());
//     ASSERT_EQ(mockArena.mArenaY, piece.getArenaY());
//
//     // When can't move
//     piece.movePiece(moveDirection::right);
//
//     // Then not moved
//     checkPos = mockArena.mArenaX;
//     ASSERT_EQ(checkPos - 1, piece.getArenaX());
//     ASSERT_EQ(mockArena.mArenaY, piece.getArenaY());
//
//     // When can't move
//     piece.movePiece(moveDirection::down);
//
//     // Then not moved
//     checkPos = mockArena.mArenaY;
//     ASSERT_EQ(mockArena.mArenaX, piece.getArenaX());
//     ASSERT_EQ(checkPos - 1, piece.getArenaY());
// }


// TEST_F(PieceTests, movePiece_moves_piece_if_object_fits)
// {
//     // Given
//     mockArena.mObjectFits = true;
//
//     // When space left
//     piece.movePiece(moveDirection::left);
//
//     // Then moved
//     int checkPos = mockArena.mArenaX;
//     ASSERT_EQ(checkPos, piece.getArenaX());
//     ASSERT_EQ(mockArena.mArenaY, piece.getArenaY());
//
//     // When space right
//     piece.movePiece(moveDirection::right);
//
//     // Then moved
//     checkPos = mockArena.mArenaX;
//     ASSERT_EQ(checkPos, piece.getArenaX());
//     ASSERT_EQ(mockArena.mArenaY, piece.getArenaY());
//
//     // When space down
//     piece.movePiece(moveDirection::down);
//
//     // Then moved
//     checkPos = mockArena.mArenaY;
//     ASSERT_EQ(mockArena.mArenaX, piece.getArenaX());
//     ASSERT_EQ(checkPos, piece.getArenaY());
// }


// TEST_F(PieceTests, movePiece_does_not_rotate_piece_if_piece_wont_fit)
// {
//     // Given
//     mockArena.mObjectFits = false;
//     piece.setCurrentRotation(Rotation::r0);
//
//     // When
//     piece.movePiece(moveDirection::rotate);
//     ASSERT_EQ(piece.getCurrentRotation(), Rotation::r0);
// }


// TEST_F(PieceTests, movePiece_rotates_90_degrees_if_piece_fits)
// {
//     // Given
//     mockArena.mObjectFits = true;
//     piece.setCurrentRotation(Rotation::r0);
//
//     // When
//     piece.movePiece(moveDirection::rotate);
//     ASSERT_EQ(piece.getCurrentRotation(), Rotation::r90);
// }


// TEST_F(PieceTests, movePiece_returns_true_if_object_fits)
// {
//     mockArena.mObjectFits = true;
//     ASSERT_TRUE(piece.movePiece(moveDirection::right ));
// }


// TEST_F(PieceTests, movePiece_returns_false_if_object_does_not_fit)
// {
//     mockArena.mObjectFits = false;
//     ASSERT_FALSE(piece.movePiece(moveDirection::down));
// }


// TEST_F(PieceTests, addPieceToArena_passes_piece_to_arena_to_update)
// {
//     // Given
//     piece.setArenaX(10);
//     piece.setArenaY(10);
//
//
//     // When
//     piece.addPieceToArena();
//
//     // Then
//     ASSERT_EQ(mockArena.mArenaX, piece.getArenaX());
//     ASSERT_EQ(mockArena.mArenaY, piece.getArenaY());
// }


// TEST_F(PieceTests, addPieceToArena_passes_current_piece_at_current_rotation_to_arena)
// {
//     // Given
//     piece.setCurrentPiece(t2);
//     piece.setCurrentRotation(r90);
//     const wchar_t* expectedRotatedTeePiece =
//        L"    "
//         "  X "
//         " XXX"
//         "    ";
//
//     // When & Then
//     piece.addPieceToArena();
//     ASSERT_STREQ(mockArena.mObjectData, expectedRotatedTeePiece);
// }


// TEST_F(PieceTests, createNewPiece_returns_false_if_piece_does_not_fit)
// {
//     mockArena.mObjectFits = false;
//     ASSERT_FALSE(piece.createNewPiece());
// }


// TEST_F(PieceTests, checkPieceFits_passes_current_piece_at_current_rotation_for_arena_to_check)
// {
//     // Given
//     const int arenaX = 10;
//     const int arenaY = 10;
//     piece.setCurrentPiece(t2);
//     piece.setCurrentRotation(r90);
//     const wchar_t* expectedRotatedTeePiece =
//        L"    "
//         "  X "
//         " XXX"
//         "    ";
//
//     // When & Then
//     piece.checkPieceFits(arenaX, arenaY);
//     ASSERT_STREQ(mockArena.mObjectData, expectedRotatedTeePiece);
// }


// TEST_F(PieceTests, on_construction_piece_registers_as_draw_item_with_screen_buffer)
// {
//     ASSERT_EQ(mockScreenBuffer.mNumRegisteredDrawItems, 1);
// }


// TEST_F(PieceTests, piece_draw_method_draws_preview_piece_to_screenBuffer)
// {
//     // Given
//     ASSERT_EQ(mockScreenBuffer.mCallCount, 0);
//
//     // When Then
//     piece.draw();
//     ASSERT_EQ(mockScreenBuffer.mCallCount, 1);
// }


// TEST_F(PieceTests, createNewPiece_returns_true_if_piece_fits)
// {
//     mockArena.mObjectFits = true;
//     ASSERT_TRUE(piece.createNewPiece());
// }
