#include "mockArena.h"
#include <iostream>

using namespace arena;

void MockArena::drawCurrentPiece(const wchar_t* piece, int height, int width, int arenaX, int arenaY)
{
    mPieceData = piece;
    mPieceHeight = height;
    mPieceWidth = width;
    mArenaX = arenaX;
    mArenaY = arenaY;
}

bool MockArena::checkObjectFits(const wchar_t* piece, int height, int width, int arenaX, int arenaY)
{
    mPieceData = piece;
    mPieceHeight = height;
    mPieceWidth = width;
    mArenaX = arenaX;
    mArenaY = arenaY;
    return mObjectFits;
}

void MockArena::addToArena(wchar_t* arena, const wchar_t* piece, int height, int width, int arenaX, int arenaY)
{
    mPieceData = piece;
    mPieceHeight = height;
    mPieceWidth = width;
    mArenaX = arenaX;
    mArenaY = arenaY;
}

wchar_t* MockArena::getArena()
{
    return mMockArena;
}