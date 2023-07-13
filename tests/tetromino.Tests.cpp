#include <gtest/gtest.h>
#include <array>
#include "tetromino.h"
#include "mockArena.h"
#include "mockScreenBuffer.h"

// using namespace piece;
using namespace tetromino;

class TetrominoTestObject : public Tetromino
{
public:
    // hacky experiment - test protected method
    friend class TetrominoTests;
    FRIEND_TEST(TetrominoTests, rotateIndex_returns_the_unrotated_index_if_rotation_is_0);
    FRIEND_TEST(TetrominoTests, rotateIndex_returns_the_90_rotated_index_if_rotation_set_to_90);
    FRIEND_TEST(TetrominoTests, rotateIndex_returns_the_180_rotated_index_if_rotation_set_to_180);
    FRIEND_TEST(TetrominoTests, rotateIndex_returns_the_270_rotated_index_if_rotation_set_to_270);
    FRIEND_TEST(TetrominoTests, rotateIndex_returns_unrotated_index_in_the_default_case);

    TetrominoTestObject(TetrominoType type, int posX, int posY) :
        Tetromino(type, posX, posY)
    {}

    int& posX = mPosX;
    int& posY = mPosY;
    TetrominoType& type = mType;
    Rotation& rotation = mRotation;

};

class TetrominoTests : public ::testing::Test
{
public:
    const int posX = 4, posY = 0;
    TetrominoType expectedType = t1;
    TetrominoTestObject mTetromino;


    TetrominoTests() :
        mTetromino(expectedType, posX, posY)
     {}
};


TEST_F(TetrominoTests, construct_tetromino_with_params)
{
    // Given
    const TetrominoType expectedType = t4;
    const int expectedX = 5, expectedY = 6;

    // When
    TetrominoTestObject tetromino = TetrominoTestObject(expectedType, expectedX, expectedY);

    // Then
    ASSERT_EQ(tetromino.type, expectedType);
    ASSERT_EQ(tetromino.posX, expectedX);
    ASSERT_EQ(tetromino.posY, expectedY);
}


TEST_F(TetrominoTests, new_tetromino_is_not_rotated)
{
    // Given
    const TetrominoType type = t4;
    const int posX = 5, posY = 6;

    // When
    TetrominoTestObject tetromino = TetrominoTestObject(type, posX, posY);

    // Then
    ASSERT_EQ(tetromino.rotation, tetromino::StartRotation);
}


TEST_F(TetrominoTests, tetromino_can_access_its_shape_data)
{
    // Given
    const int posX = 3, posY = 2;
    TetrominoType expectedType = t1;
    TetrominoTestObject tetromino1 = TetrominoTestObject(expectedType, posX, posY);
    const wchar_t* expectedData = L"  X "
                                   "  X "
                                   "  X "
                                   "  X ";

    // When Then
    ASSERT_STREQ(tetromino1.Data(expectedType), expectedData);


    // Given
    expectedType = t7;
    TetrominoTestObject tetromino2 = TetrominoTestObject(expectedType, posX, posY);
    expectedData = L"  X "
                    "  X "
                    " XX "
                    "    ";

    // When Then
    ASSERT_STREQ(tetromino2.Data(expectedType), expectedData);
}


TEST_F(TetrominoTests, rotateIndex_returns_the_unrotated_index_if_rotation_is_0)
{
    // no rotation so expected = (y * width) + x

    // 0  1  2  3
    // 4  5  6  7
    // 8  9  10 11
    // 12 13 14 15

    // Given
    const int width = 4, height = 4;
    const Rotation rotation = r0;
    int x = 0, y = 0, expectedIndex = 0; // 0*4 + 0

    // When & Then
    int rotatedIndex = mTetromino.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);


    // Given
    x = 1; y = 0; expectedIndex = 1; // 0*4 + 1

    // When & Then
    rotatedIndex = mTetromino.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, 1);


    // Given
    x = 3; y = 3; expectedIndex = 15; // 3*4 + 3

    // When & Then
    rotatedIndex = mTetromino.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);
}


TEST_F(TetrominoTests, rotateIndex_returns_the_90_rotated_index_if_rotation_set_to_90)
{
    // 90 deg rotation so expected = ( (height - 1) * width ) + y - (x * width)

    // 12 8  4  0
    // 13 9  5  1
    // 14 10 6  2
    // 15 11 7  3

    // Given
    const int width = 4, height = 4;
    const Rotation rotation = r90;
    int x = 0, y = 0, expectedIndex = 12; // (4-1)*4 + 0 - (0 * 4)

    // When & Then
    int rotatedIndex = mTetromino.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);


    // Given
    x = 1; y = 0; expectedIndex = 8; // (4-1)*4 + 0 - (1 * 4)

    // When & Then
    rotatedIndex = mTetromino.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);


    // Given
    x = 3; y = 3; expectedIndex = 3; // (4-1)*4 + 3 - (3 * 4)

    // When & Then
    rotatedIndex = mTetromino.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);
}


TEST_F(TetrominoTests, rotateIndex_returns_the_180_rotated_index_if_rotation_set_to_180)
{
    // 180 deg rotation so expected = ( height * width - 1 ) - ( y * 4 ) - x

    // 15 14 13 12
    // 11 10 9  8
    // 7  6  5  4
    // 3  2  1  0

    // Given
    const int width = 4, height = 4;
    const Rotation rotation = r180;
    int x = 0, y = 0, expectedIndex = 15; // (4*4 - 1) - ( 0 * 4) - 0

    // When & Then
    int rotatedIndex = mTetromino.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);


    // Given
    x = 1; y = 0; expectedIndex = 14; // (4*4 - 1) - ( 0 * 4) - 1

    // When & Then
    rotatedIndex = mTetromino.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);


    // Given
    x = 3; y = 3; expectedIndex = 0; // (4*4 - 1) - ( 3 * 4) - 3

    // When & Then
    rotatedIndex = mTetromino.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);
}


TEST_F(TetrominoTests, rotateIndex_returns_the_270_rotated_index_if_rotation_set_to_270)
{
    // 270 deg rotation so expected = (width - 1) - y + ( x * height )

    // 3  7  11 15
    // 2  6  10 14
    // 1  5  9  13
    // 0  4  8  12

    // Given
    const int width = 4, height = 4;
    const Rotation rotation = r270;
    int x = 0, y = 0, expectedIndex = 3; // (4-1) - 0 + (0 * 4)

    // When & Then
    int rotatedIndex = mTetromino.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);


    // Given
    x = 1; y = 0; expectedIndex = 7; // (4-1) - 0 + (1 * 4)

    // When & Then
    rotatedIndex = mTetromino.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);


    // Given
    x = 3; y = 3; expectedIndex = 12; // (4-1) - 3 + (3 * 4)

    // When & Then
    rotatedIndex = mTetromino.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);
}


TEST_F(TetrominoTests, rotateIndex_returns_unrotated_index_in_the_default_case)
{
    // Given
    const int width = 4, height = 4;
    const Rotation rotation = rotationCount;
    int x = 1, y = 0, expectedIndex = 1; // unrotated

    // When & Then
    int rotatedIndex = mTetromino.rotateIndex(x, y, width, height, rotation);
    ASSERT_EQ(rotatedIndex, expectedIndex);
}


TEST_F(TetrominoTests, rotatePiece_rotates_current_piece_and_copies_to_buffer)
{
    // Given - rotate tee piece 90 degrees
    int height = TetrominoHeight;
    int width = TetrominoHeight;

    wchar_t pieceBuffer[height * width];
    pieceBuffer[width * height] = '\0';

    mTetromino.SetType(t2);
    // unrotated piece
    // "  X "
    // " XX "
    // "  X "
    // "    "

    mTetromino.SetRotation(Rotation::r90);
    const wchar_t* expectedRotatedTeePiece =
       L"    "
        "  X "
        " XXX"
        "    ";

    // When & Then
    mTetromino.rotatePiece(pieceBuffer, mTetromino.Type(), mTetromino.GetRotation(), height, width);
    ASSERT_STREQ(pieceBuffer, expectedRotatedTeePiece);


    // Given - rotate long piece 270 degrees
    mTetromino.SetType(t1);
    // unrotated piece
    // "  X "
    // "  X "
    // "  X "
    // "  X ";

    mTetromino.SetRotation(Rotation::r270);
    const wchar_t* expectedRotatedLongPiece =
       L"    "
        "XXXX"
        "    "
        "    ";

    // When & Then
    mTetromino.rotatePiece(pieceBuffer, mTetromino.Type(), mTetromino.GetRotation(), height, width);
    ASSERT_STREQ(pieceBuffer, expectedRotatedLongPiece);
}
