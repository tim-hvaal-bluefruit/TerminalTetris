#include "mockArena.h"
#include <iostream>

using namespace arena;

void MockArena::drawCurrentPiece(const wchar_t* piece, int height, int width, int arenaX, int arenaY)
{
    copyToMockObject(piece, height, width);
    mObjectHeight = height;
    mObjectWidth = width;
    mArenaX = arenaX;
    mArenaY = arenaY;
}

bool MockArena::checkObjectFits(const wchar_t* piece, int height, int width, int arenaX, int arenaY)
{
    copyToMockObject(piece, height, width);
    mObjectHeight = height;
    mObjectWidth = width;
    mArenaX = arenaX;
    mArenaY = arenaY;
    return mObjectFits;
}

void MockArena::addToArena(wchar_t* arena, const wchar_t* piece, int height, int width, int arenaX, int arenaY)
{
    copyToMockObject(piece, height, width);
    mObjectHeight = height;
    mObjectWidth = width;
    mArenaX = arenaX;
    mArenaY = arenaY;
}

void MockArena::copyToMockObject(const wchar_t* object, int height, int width)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int index = (y * width) + x;
            mObjectData[index] = object[index];
        }
    }
    mObjectData[height * width] = '\0';
}