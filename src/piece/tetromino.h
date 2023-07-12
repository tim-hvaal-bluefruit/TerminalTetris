#pragma once
#include <iostream>

namespace tetromino
{

enum TetrominoType { t1 = 0, t2, t3, t4, t5, t6, t7, typeCount };
enum Rotation { r0 = 0, r90, r180, r270, rotationCount };
enum moveDirection { left = 0, right, down, rotate, directionCount };

struct TetrominoData
{
    std::wstring mTetrominoData[TetrominoType::typeCount];
    TetrominoData()
    {
        mTetrominoData[TetrominoType::t1].append(L"  X "
                                                  "  X "
                                                  "  X "
                                                  "  X ");

        mTetrominoData[TetrominoType::t2].append(L"  X "
                                                  " XX "
                                                  "  X "
                                                  "    ");

        mTetrominoData[TetrominoType::t3].append(L"    "
                                                  " XX "
                                                  " XX "
                                                  "    ");

        mTetrominoData[TetrominoType::t4].append(L"  X "
                                                  " XX "
                                                  " X  "
                                                  "    ");

        mTetrominoData[TetrominoType::t5].append(L" X  "
                                                  " XX "
                                                  "  X "
                                                  "    ");

        mTetrominoData[TetrominoType::t6].append(L" X  "
                                                  " X  "
                                                  " XX "
                                                  "    ");

        mTetrominoData[TetrominoType::t7].append(L"  X "
                                                  "  X "
                                                  " XX "
                                                  "    ");
    }
};

static const TetrominoData ShapeData;
static constexpr int TetrominoHeight = 4;
static constexpr int TetrominoWidth = 4;
static constexpr int TetrominoSize = TetrominoHeight * TetrominoWidth;
static constexpr Rotation StartRotation = Rotation::r0;


class Tetromino
{
public:
    Tetromino(TetrominoType type, int posX, int posY);
    int rotateIndex(int x, int y, int width, int height, Rotation rotation);
    void rotatePiece(wchar_t* data, TetrominoType type, Rotation rotation, int height, int width);

    // Get
    const wchar_t* Data(TetrominoType type);
    TetrominoType Type();
    Rotation GetRotation();
    int PosX();
    int PosY();

    // Set
    void SetType(TetrominoType type);
    void SetRotation(Rotation rotation);
    void SetPosX(int arenaX);
    void SetPosY(int arenaY);

protected:
    TetrominoType mType;
    Rotation mRotation = StartRotation;
    int mPosX;
    int mPosY;

private:
    const TetrominoData& mData;
};

} // namespace tetromino
