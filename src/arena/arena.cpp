#include "arena.h"

using namespace arena;


void Arena::drawArena()
{
    mScreenBuffer.drawToBuffer(mArena, mArenaHeight, mArenaWidth, mScreenOffsetX, mScreenOffsetY);
}


wchar_t* Arena::createArena()
{
    generateArena();
    return mArena;
}


wchar_t* Arena::createArena(int arenaHeight, int arenaWidth, int xOffset, int yOffset)
{
    mArenaHeight = arenaHeight;
    mArenaWidth = arenaWidth;
    generateArena();
    return mArena;
}


void Arena::generateArena()
{
    for(int x = 0; x < mArenaWidth; x++)
    for (int y = 0; y < mArenaHeight; y++)
        mArena[y * mArenaWidth + x] = (x == 0 || x == mArenaWidth - 1 || y == mArenaHeight - 1) ? '#' : blankChar;

    mArena[mArenaHeight * mArenaWidth] = '\0';
}


void Arena::addToArena(wchar_t* obj, int height, int width, int arenaX, int arenaY)
{
    int ix, iy;
    for(iy = 0; iy < height; iy++)
    {
        for(ix = 0; ix < width; ix++)
        {
            char c = obj[iy * width + ix];
            if (c != blankChar)
                mArena[ ((arenaY + iy) * mArenaWidth) + (arenaX + ix) ] = c;
        }
    }
}
