#include "piece.h"

using namespace piece;

void Piece::drawCurrentPiece()
{
    const wchar_t* pieceData = getPieceData(mCurrentPiece);
    mArena.drawCurrentPiece(pieceData, defaultPieceHeight, defaultPieceWidth, mArenaX, mArenaY);
}

void Piece::drawPreviewPiece()
{
    const wchar_t* pieceData = getPieceData(mPreviewPiece);
    mScreenBuffer.drawToBuffer(pieceData, defaultPieceHeight, defaultPieceWidth, 20, 6);
}

bool Piece::createNewPiece()
{
    mCurrentPiece = mPreviewPiece;
    if(!checkPieceFits(arena::defaultStartPositionX, arena::defaultStartPositionY))
    {
        mArenaX = arena::defaultStartPositionX;
        mArenaY = arena::defaultStartPositionY;
        return false;
    }

    mArenaX = arena::defaultStartPositionX;
    mArenaY = arena::defaultStartPositionY;
    mPreviewPiece = static_cast<pieceIndex>(rand() % 7);
    return true;
}

bool Piece::movePiece(moveDirection direction)
{
    switch(direction)
    {
        case (moveDirection::left):
        {
            if(checkPieceFits(mArenaX - 1, mArenaY))
            {
                mArenaX--;
                return true;
            }
            break;
        }
        case (moveDirection::right):
        {
            if(checkPieceFits(mArenaX + 1, mArenaY))
            {
                mArenaX++;
                return true;
            }
            break;
        }
        case (moveDirection::down):
        {
            if(checkPieceFits(mArenaX, mArenaY + 1))
            {
                mArenaY++;
                return true;
            }
            break;
        }
        default:
            break;
    }
    return false;
}

bool Piece::checkPieceFits(int arenaX, int arenaY)
{
    return mArena.checkObjectFits(getPieceData(mCurrentPiece), defaultPieceHeight, defaultPieceWidth, arenaX, arenaY);
}

void Piece::addPieceToArena()
{
    mArena.addToArena(mArena.getArena(), getPieceData(mCurrentPiece), defaultPieceHeight, defaultPieceWidth, mArenaX, mArenaY);
}

int Piece::rotateIndex(int x, int y, int width, rotation rotation)
{
    int rotatedIndex = (y * width) + x;
    return rotatedIndex;
}




// // ROTATE PLAN

// piece
// 0  1  2  3
// 4  5  6  7
// 8  9  10 11
// 12 13 14 15

// rotated piece
// 12 8  4  0
// 13 9  5  1
// 14 10 6  2
// 15 11 7  3

// 0 rotation is easy
//   index = y * width + x

// so for each pixel
//   rotated[ ( y * width) + x ] = piece[ ( y * width) + x ]

// 90 rotation
//   rotated[ ( y * width) + x ] = piece[ 12 + y - (x * width) ] 0 becomes 12 // when y = 0 x = 0
//   rotated[ ( y * width) + x ] = piece[ 12 + y - (x * width) ] 1 becomes 8 // when y = 0 x = 1
//   rotated[ ( y * width) + x ] = piece[ 12 + y - (x * width) ] 2 becomes 4 // when y = 0 x = 2
//   rotated[ ( y * width) + x ] = piece[ 12 + y - (x * width) ] 3 becomes 0 // when y = 0 x = 3

// 180 rotation
//  index = 15 - (y * width) - x

// 270 rotation
//  index = 3 - y + (x * 4)

