#pragma once
#include "arena.h"
#include "screenBuffer.h"
#include "pieceInterface.h"
#include <string>

namespace piece
{
class Piece : public PieceInterface
{

public:
    Piece(arena::ArenaInterface& arena, screen::ScreenBufferInterface& screenBuffer) :
        mArena(arena),
        mScreenBuffer(screenBuffer)
    {
        mPieces[p1].append(L"  X   X   X   X ");
	    mPieces[p2].append(L"  X  XX   X     ");
	    mPieces[p3].append(L"     XX  XX     ");
	    mPieces[p4].append(L"  X  XX  X      ");
	    mPieces[p5].append(L" X   XX   X     ");
	    mPieces[p6].append(L" X   X   XX     ");
	    mPieces[p7].append(L"  X   X  XX     ");

        srand(time(NULL));
        mCurrentPiece = static_cast<pieceIndex>(rand() % 7);
        mArenaX = arena::defaultStartPositionX;
        mArenaY = arena::defaultStartPositionY;

        mPreviewPiece = static_cast<pieceIndex>(rand() % 7);
    }

    void drawCurrentPiece() override;
    void drawPreviewPiece() override;
    const wchar_t* getPieceData(pieceIndex pieceIdx) {return mPieces[pieceIdx].c_str();}
    void createNewPiece();
    void movePiece(moveDirection direction) override;

    // Getters and Setters
    void setCurrentPiece(pieceIndex piece) {mCurrentPiece = piece;}
    pieceIndex getCurrentPiece() {return mCurrentPiece;}

    void setPreviewPiece(pieceIndex piece) {mPreviewPiece = piece;}
    pieceIndex getPreviewPiece() {return mPreviewPiece;}

    void setArenaX(int arenaX) {mArenaX = arenaX;}
    int getArenaX() {return mArenaX;}

    void setArenaY(int arenaY) {mArenaY = arenaY;}
    int getArenaY() {return mArenaY;}

private:
    arena::ArenaInterface& mArena;
    screen::ScreenBufferInterface& mScreenBuffer;
    std::wstring mPieces[pieceCount];
    pieceIndex mCurrentPiece;
    int mArenaX = 0;
    int mArenaY = 0;

    pieceIndex mPreviewPiece;
};
} // namespace piece


// next piece = random number 0-6
// block attaches
// int mCurrentPiece = mPreviewPiece
// next piece = random number 0-6