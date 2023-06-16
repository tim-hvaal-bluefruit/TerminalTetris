#include "arena.h"

using namespace arena;


void Arena::drawArena()
{
    mScreenBuffer.drawToBuffer(mArena, mArenaHeight, mArenaWidth, mScreenOffsetX, mScreenOffsetY);
}


wchar_t* Arena::createArena()
{
    refreshArena(mArena);
    refreshArena(mActiveArena);
    return mArena;
}


wchar_t* Arena::createArena(int arenaHeight, int arenaWidth)
{
    mArenaHeight = arenaHeight;
    mArenaWidth = arenaWidth;
    refreshArena(mArena);
    refreshArena(mActiveArena);
    return mArena;
}


void Arena::refreshArena(wchar_t* arena)
{
    for(int x = 0; x < mArenaWidth; x++)
    for (int y = 0; y < mArenaHeight; y++)
        arena[y * mArenaWidth + x] = (x == 0 || x == mArenaWidth - 1 || y == mArenaHeight - 1) ? '#' : blankChar;

    arena[mArenaHeight * mArenaWidth] = '\0';
}


void Arena::addToArena(wchar_t* arena, const wchar_t* obj, int height, int width, int arenaX, int arenaY)
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

void Arena::drawCurrentPiece(const wchar_t* piece, const int height, const int width, const int arenaX, const int arenaY)
{
    refreshArena(mActiveArena);
    addToArena(mActiveArena, piece, height, width, arenaX, arenaY);
    mScreenBuffer.drawToBuffer(mActiveArena, mArenaHeight, mArenaWidth, mScreenOffsetX, mScreenOffsetY);
}


bool Arena::checkObjectFits(const wchar_t* obj, int height, int width, int arenaX, int arenaY)
{
    // check arenaX and arenaY are less than mArena height and width
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            char c = obj[y * width + x];
            if (c == blankChar)
                continue;
            if (mArena[((arenaY + y) * mArenaWidth) + (arenaX + x)] != blankChar)
                return false;
        }
    }
    return true;
}

