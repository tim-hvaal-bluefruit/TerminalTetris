#include "arena.h"

using namespace arena;


void Arena::drawArena()
{
    mScreenBuffer.drawToBuffer(mArena, mArenaHeight, mArenaWidth, mScreenOffsetX, mScreenOffsetY);
}


wchar_t* Arena::createArena()
{
    generateArena(mArena);
    return mArena;
}


wchar_t* Arena::createArena(int arenaHeight, int arenaWidth)
{
    mArenaHeight = arenaHeight;
    mArenaWidth = arenaWidth;
    generateArena(mArena);
    return mArena;
}


void Arena::generateArena(wchar_t* arena)
{
    for(int x = 0; x < mArenaWidth; x++)
    for (int y = 0; y < mArenaHeight; y++)
        mArena[y * mArenaWidth + x] = (x == 0 || x == mArenaWidth - 1 || y == mArenaHeight - 1) ? '#' : blankChar;

    arena[mArenaHeight * mArenaWidth] = '\0';
}


void Arena::addToArena(wchar_t* arena, wchar_t* obj, int height, int width, int arenaX, int arenaY)
{
    int ix, iy;
    for(iy = 0; iy < height; iy++)
    {
        for(ix = 0; ix < width; ix++)
        {
            char c = obj[iy * width + ix];
            if (c != blankChar)
                arena[ ((arenaY + iy) * mArenaWidth) + (arenaX + ix) ] = c;
        }
    }
}
