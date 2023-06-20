#include "piece.h"

using namespace piece;

void Piece::drawCurrentPiece()
{
    int height = defaultPieceHeight;
    int width = defaultPieceWidth;
    wchar_t pieceBuffer[height * width];

    rotatePiece(pieceBuffer, mCurrentPiece, mCurrentRotation, height, width);

    mArena.drawCurrentPiece(pieceBuffer, height, width, mArenaX, mArenaY);
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
        case (moveDirection::rotate):
        {
            if(checkPieceFits(mArenaX, mArenaY))
            {
                int r = (int)getCurrentRotation();
                r = (r + 1) % rotation::rotationCount;
                setCurrentRotation((rotation)r);
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
    int height = defaultPieceHeight;
    int width = defaultPieceWidth;

    wchar_t pieceBuffer[height * width];
    rotatePiece(pieceBuffer, mCurrentPiece, mCurrentRotation, height, width);

    return mArena.checkObjectFits(pieceBuffer, height, width, arenaX, arenaY);
}


void Piece::rotatePiece(wchar_t* pieceData, pieceIndex piece, rotation rotation, int height, int width)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int currentIndex = (y * width) + x;
            int rotatedIndex = rotateIndex(x, y, width, height, rotation);
            pieceData[currentIndex] = getPieceData(piece)[rotatedIndex];
        }
    }
}


void Piece::addPieceToArena()
{
    int height = defaultPieceHeight;
    int width = defaultPieceWidth;

    wchar_t pieceBuffer[height * width];
    rotatePiece(pieceBuffer, mCurrentPiece, mCurrentRotation, height, width);

    mArena.addToArena(mArena.getArena(), pieceBuffer, height, width, mArenaX, mArenaY);
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
