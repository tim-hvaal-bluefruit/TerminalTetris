#include "piece.h"
#include <stdio.h>
#include <ctime>

using namespace piece;

void Piece::drawCurrentPiece()
{
    const wchar_t* pieceData = getPieceData(mCurrentPiece);
    mArena.drawCurrentPiece(pieceData, defaultPieceHeight, defaultPieceWidth, mArenaX, mArenaY);
}

void Piece::createNewPiece()
{
    mCurrentPiece = mPreviewPiece;
    mRotation = mPreviewRotation;
    mArenaX = arena::defaultStartPositionX;
    mArenaY = arena::defaultStartPositionY;
    srand(time(NULL));
    mPreviewPiece = static_cast<pieceIndex>(rand() % 7);
    mPreviewRotation = static_cast<pieceIndex>(rand() % 4);
}

void Piece::movePiece(moveDirection direction)
{
    switch(direction)
    {
        case (moveDirection::left):
        {
            mArenaX--;
            break;
        }
        case (moveDirection::right):
        {
            mArenaX++;
            break;
        }
        case (moveDirection::down):
        {
            mArenaY++;
            break;
        }
        default:
        {
            break;
        }
    }
}