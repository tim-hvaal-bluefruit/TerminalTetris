#include "piece.h"

using namespace piece;

void Piece::drawCurrentPiece()
{
    const wchar_t* pieceData = getPieceData(mCurrentPiece);
    mArena.drawCurrentPiece(pieceData, defaultPieceHeight, defaultPieceWidth, mArenaX, mArenaY);
}

void Piece::createNewPiece()
{
    mCurrentPiece = mNextPiece;
    mArenaX = arena::defaultStartPositionX;
    mArenaY = arena::defaultStartPositionY;
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