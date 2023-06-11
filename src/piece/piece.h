#pragma once
#include "arena.h"
#include <string>

namespace piece
{
    constexpr int defaultPieceHeight = 4;
    constexpr int defaultPieceWidth = 4;
    enum pieceIndex { p1 = 0, p2, p3, p4, p5, p6, p7, pieceCount};
    enum moveDirection { left = 0, right, down};

class Piece
{

public:
    Piece(arena::ArenaInterface& arena) :
        mArena(arena)
    {
        mPieces[p1].append(L"..X...X...X...X.");
	    mPieces[p2].append(L"..X..XX...X.....");
	    mPieces[p3].append(L".....XX..XX.....");
	    mPieces[p4].append(L"..X..XX..X......");
	    mPieces[p5].append(L".X...XX...X.....");
	    mPieces[p6].append(L".X...X...XX.....");
	    mPieces[p7].append(L"..X...X..XX.....");
    }

    void drawCurrentPiece();
    const wchar_t* getPieceData(pieceIndex pieceIdx) {return mPieces[pieceIdx].c_str();}
    void createNewPiece();
    void movePiece(moveDirection direction);

    // Getters and Setters
    void setCurrentPiece(pieceIndex piece) {mCurrentPiece = piece;}
    pieceIndex getCurrentPiece() {return mCurrentPiece;}

    void setNextPiece(pieceIndex piece) {mNextPiece = piece;}
    pieceIndex getNextPiece() {return mNextPiece;}

    void setArenaX(int arenaX) {mArenaX = arenaX;}
    int getArenaX() {return mArenaX;}

    void setArenaY(int arenaY) {mArenaY = arenaY;}
    int getArenaY() {return mArenaY;}

private:
    arena::ArenaInterface& mArena;
    std::wstring mPieces[pieceCount];
    pieceIndex mCurrentPiece = pieceCount;
    int mArenaX = 0;
    int mArenaY = 0;

    pieceIndex mNextPiece = pieceCount;
};
} // namespace piece


// next piece = random number 0-6
// block attaches
// int mCurrentPiece = mNextPiece
// next piece = random number 0-6