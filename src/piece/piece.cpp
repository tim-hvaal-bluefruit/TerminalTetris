#include "piece.h"

using namespace piece;
using namespace tetromino;


Piece::Piece(arena::ArenaInterface& arena, screen::ScreenBufferInterface& screenBuffer) :
    mArena(arena),
    mScreenBuffer(screenBuffer)
{
    mPieces[t1].append(L"  X   X   X   X ");
    mPieces[t2].append(L"  X  XX   X     ");
    mPieces[t3].append(L"     XX  XX     ");
    mPieces[t4].append(L"  X  XX  X      ");
    mPieces[t5].append(L" X   XX   X     ");
    mPieces[t6].append(L" X   X   XX     ");
    mPieces[t7].append(L"  X   X  XX     ");

    srand(time(NULL));
    mCurrentPiece = static_cast<TetrominoType>(rand() % 7);
    mArenaX = arena::defaultStartPositionX;
    mArenaY = arena::defaultStartPositionY;

    mPreviewPiece = static_cast<TetrominoType>(rand() % 7);

    mScreenBuffer.registerDrawItem(this);
}


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
    mPreviewPiece = static_cast<TetrominoType>(rand() % 7);
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
            int r = (int)getCurrentRotation();
            r = (r + 1) % Rotation::rotationCount;
            setCurrentRotation((Rotation)r);

            if(checkPieceFits(mArenaX, mArenaY))
            {
                return true;
            }

            r = (r + 3) % Rotation::rotationCount;
            setCurrentRotation((Rotation)r);
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


void Piece::rotatePiece(wchar_t* pieceData, TetrominoType piece, Rotation rotation, int height, int width)
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


int Piece::rotateIndex(int x, int y, int width, int height, Rotation rotation)
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


void Piece::draw()
{
    drawPreviewPiece();
}



//==============================================================================
// Tetromino
//==============================================================================


Tetromino::Tetromino(TetrominoData& data, piece::TetrominoType type, int posX, int posY) :
    mData(data),
    mType(type),
    mPosX(posX),
    mPosY(posY)
{
}

const wchar_t* Tetromino::Data(piece::TetrominoType type)
{
    return mData.mTetrominoData[type].c_str();
}