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

void Piece::createNewPiece()
{
    mCurrentPiece = mPreviewPiece;
    mArenaX = arena::defaultStartPositionX;
    mArenaY = arena::defaultStartPositionY;
    mPreviewPiece = static_cast<pieceIndex>(rand() % 7);
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