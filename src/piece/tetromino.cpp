#include "tetromino.h"

using namespace tetromino;

Tetromino::Tetromino(TetrominoType type, int posX, int posY) :
    mData(tetromino::ShapeData),
    mType(type),
    mPosX(posX),
    mPosY(posY)
{
}

const wchar_t* Tetromino::Data(TetrominoType type)
{
    return mData.mTetrominoData[type].c_str();
}

TetrominoType Tetromino::Type()
{
    return mType;
}

Rotation Tetromino::GetRotation()
{
    return mRotation;
}

int Tetromino::PosX()
{
    return mPosX;
}

int Tetromino::PosY()
{
    return mPosY;
}

void Tetromino::SetType(TetrominoType type)
{
    mType = type;
}

void Tetromino::SetRotation(Rotation rotation)
{
    mRotation = rotation;
}

void Tetromino::SetPosX(int arenaX)
{
    mPosX = arenaX;
}

void Tetromino::SetPosY(int arenaY)
{
    mPosY = arenaY;
}

int Tetromino::rotateIndex(int x, int y, int width, int height, Rotation rotation)
{
    int rotatedIndex = 0;
    switch (rotation)
    {
        case (Rotation::r0):
            return rotatedIndex = (y * width) + x;

        case (Rotation::r90):
            return rotatedIndex = ((height - 1) * width) + y - (x * width);

        case (Rotation::r180):
            return rotatedIndex = ( ( height * width ) - 1 ) - ( y * width ) - x;

        case (Rotation::r270):
            return rotatedIndex = (width - 1) - y + (x * height);

        default:
            return rotatedIndex = (y * width) + x;
    }
}

void Tetromino::rotatePiece(wchar_t* data, TetrominoType type, Rotation rotation, int height, int width)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int currentIndex = (y * width) + x;
            int rotatedIndex = rotateIndex(x, y, width, height, rotation);
            data[currentIndex] = Data(type)[rotatedIndex];
        }
    }
}
