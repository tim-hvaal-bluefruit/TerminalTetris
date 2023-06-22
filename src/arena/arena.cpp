#include "windows.h"
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
    mScreenBuffer.drawVisibleToBuffer(mActiveArena, mArenaHeight, mArenaWidth, mScreenOffsetX, mScreenOffsetY);
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


bool Arena::checkLineComplete(int arenaY)
{
    for (int x = 0; x < mArenaWidth; x++)
    {
        const int index = (arenaY * mArenaWidth) + x;
        if (mArena[index] == blankChar)
            return false;
    }
    return true;
}


int Arena::checkAllLines()
{
    int numLines = 0;
    for (int yPos = 0; yPos < mArenaHeight - 1; yPos++) // don't check base
    {
        if (checkLineComplete(yPos))
        {
            numLines++;
            destroyLine(yPos);
            moveStackDown(yPos);
        }
    }
    return numLines;
}


void Arena::destroyLine(int yPos)
{
    for (int x = 1; x < mArenaWidth - 1; x++) // don't check sides
    {
        mArena[ (yPos * mArenaWidth) + x] = '=';
        animate(destroyLineAnimationSpeedMs + x); // speeds up
    }

    for (int x = 1; x < mArenaWidth - 1; x++)
    {
        mArena[ (yPos * mArenaWidth) + x] = ' ';
        animate(destroyLineAnimationSpeedMs + x);
    }
}


void Arena::animate(int frameLengthMs)
{
    drawArena();
    mConsole.animateFrame(frameLengthMs, mScreenBuffer.buffer(), consoleSize);
}


void Arena::moveStackDown(int rowPosY)
{
    int startPos = (rowPosY * mArenaWidth) + mArenaWidth;

    for(int i = startPos; i > mArenaWidth; i--)
        mArena[i] = mArena[i - mArenaWidth];

    // blank top row and avoid sides
    for (int x = mArenaWidth - 2; x > 0; x--)
        mArena[x] = blankChar;

    animate(stackFallAnimationDelayMs);
}


void Arena::gameOverFlames()
{
    int i = 0;
    while(5 > i++)
    {
        for(int y = mArenaHeight - 2; y >= 0; y--)
        {
            for(int x = 1; x < mArenaWidth - 1; x++)
            {
                int index = (y * mArenaWidth) + x;
                mArena[index] = L"Vv"[rand() % 2];
            }
            animate(flameAnimationSpeedMs);
        }
    }

    for(int y = 0; y < mArenaHeight - 1; y++)
    {
        for(int x = 1; x < mArenaWidth - 1; x++)
        {
            int index = (y * mArenaWidth) + x;
            mArena[index] = blankChar;
        }
        animate(flameAnimationSpeedMs - i);
    }
}

