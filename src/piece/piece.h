#pragma once
#include <string>

namespace piece
{

enum pieceIndex { p1 = 0, p2, p3, p4, p5, p6, p7, pieceCount};

class Piece
{

public:
    Piece()
    {
        mPieces[p1].append(L"..X...X...X...X.");
	    mPieces[p2].append(L"..X..XX...X.....");
	    mPieces[p3].append(L".....XX..XX.....");
	    mPieces[p4].append(L"..X..XX..X......");
	    mPieces[p5].append(L".X...XX...X.....");
	    mPieces[p6].append(L".X...X...XX.....");
	    mPieces[p7].append(L"..X...X..XX.....");
    }
    void setCurrentPiece(pieceIndex piece) {mCurrentPiece = piece;}
    pieceIndex getCurrentPiece() {return mCurrentPiece;}

    const wchar_t* getPieceData(int pieceIdx) {return mPieces[pieceIdx].c_str();}

private:
    std::wstring mPieces[pieceCount];
    pieceIndex mCurrentPiece = pieceCount;
};
} // namespace piece


// next piece = random number 0-6
// block attaches
// int mCurrentPiece = mNextPiece
// next piece = random number 0-6