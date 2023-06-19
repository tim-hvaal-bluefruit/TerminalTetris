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


int Piece::rotateIndex(int x, int y, int width, int height, rotation rotation)
{
    int rotatedIndex = 0;
    switch (rotation)
    {
        case (rotation::r0):
            return rotatedIndex = (y * width) + x;

        case (rotation::r90):
            return rotatedIndex = ((height - 1) * width) + y - (x * width);

        case (rotation::r180):
            return rotatedIndex = ( ( height * width ) - 1 ) - ( y * width ) - x;

        case (rotation::r270):
            return rotatedIndex = (width - 1) - y + (x * height);

        default:
            return rotatedIndex = (y * width) + x;
    }
}
