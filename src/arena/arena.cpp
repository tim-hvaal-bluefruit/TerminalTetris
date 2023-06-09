#include "arena.h"

using namespace arena;

void Arena::drawArena()
{
    mScreenBuffer.drawToBuffer(mArena, mArenaHeight, mArenaWidth, mXOffset, mYOffset);
}

// TODO - DRY violation
wchar_t* Arena::createArena()
{
    for(int x = 0; x < mArenaWidth; x++)
        for (int y = 0; y < mArenaHeight; y++)
            mArena[y * mArenaWidth + x] = (x == 0 || x == mArenaWidth - 1 || y == mArenaHeight - 1) ? '#' : '.';

    mArena[mArenaHeight * mArenaWidth] = '\0';
    return mArena;
}

wchar_t* Arena::createArena(int arenaHeight, int arenaWidth, int xOffset, int yOffset)
{
    mArenaHeight = arenaHeight;
    mArenaWidth = arenaWidth;
    for(int x = 0; x < mArenaWidth; x++)
        for (int y = 0; y < mArenaHeight; y++)
            mArena[y * mArenaWidth + x] = (x == 0 || x == mArenaWidth - 1 || y == mArenaHeight - 1) ? '#' : '.';

    mArena[mArenaHeight * mArenaWidth] = '\0';
    return mArena;
}
