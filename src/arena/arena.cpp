#include "windows.h"
#include "arena.h"

using namespace arena;

Arena::Arena(screen::ScreenBufferInterface& screenBuffer, console::ConsoleInterface& console) :
    mScreenBuffer(screenBuffer),
    mConsole(console),
    mArenaHeight(DefaultArenaHeight),
    mArenaWidth(DefaultArenaWidth),
    mCurrentPiece(DefaultTetromino, TetrominoStartPositionX, TetrominoStartPositionY)
{
    mScreenBuffer.registerDrawItem(this);
}

void Arena::draw()
{
    drawArena();
}

void Arena::drawArena()
{
    mScreenBuffer.drawToBuffer(mArena, mArenaHeight, mArenaWidth, arena::ArenaDisplayOffsetX, arena::ArenaDisplayOffsetY);
}

void Arena::drawCurrentPiece(const wchar_t* piece, const int height, const int width, const int arenaX, const int arenaY)
{
    refreshArena(mActiveArena);
    addToArena(mActiveArena, piece, height, width, arenaX, arenaY);
    mScreenBuffer.drawVisibleToBuffer(mActiveArena, mArenaHeight, mArenaWidth, arena::ArenaDisplayOffsetX, arena::ArenaDisplayOffsetY);
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

wchar_t* Arena::getArena()
{
    return mArena;
}

void Arena::refreshArena(wchar_t* arena)
{
    for(int x = 0; x < mArenaWidth; x++)
    for (int y = 0; y < mArenaHeight; y++)
        arena[y * mArenaWidth + x] = (x == 0 || x == mArenaWidth - 1 || y == mArenaHeight - 1) ? '#' : BlankChar;

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
            if (c != BlankChar)
                arena[ ((arenaY + iy) * mArenaWidth) + (arenaX + ix) ] = c;
        }
    }
}

bool Arena::checkObjectFits(const wchar_t* obj, int height, int width, int arenaX, int arenaY)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            char c = obj[y * width + x];
            if (c == BlankChar)
                continue;
            if (mArena[((arenaY + y) * mArenaWidth) + (arenaX + x)] != BlankChar)
                return false;
        }
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

    if(numLines > 0)
    {
        notify(observer::Event::linesCompleted, numLines);
    }

    return numLines;
}

bool Arena::checkLineComplete(int arenaY)
{
    for (int x = 0; x < mArenaWidth; x++)
    {
        const int index = (arenaY * mArenaWidth) + x;
        if (mArena[index] == BlankChar)
            return false;
    }
    return true;
}

void Arena::destroyLine(int yPos)
{
    for (int x = 1; x < mArenaWidth - 1; x++) // don't check sides
    {
        mArena[ (yPos * mArenaWidth) + x] = '=';
        animate(DestroyLineAnimationSpeedMs + x); // speeds up
    }

    for (int x = 1; x < mArenaWidth - 1; x++)
    {
        mArena[ (yPos * mArenaWidth) + x] = ' ';
        animate(DestroyLineAnimationSpeedMs + x);
    }
}

void Arena::animate(int frameLengthMs)
{
    drawArena();
    mConsole.animateFrame(frameLengthMs, mScreenBuffer.buffer(), console::consoleSize);
}

void Arena::moveStackDown(int rowPosY)
{
    int startPos = (rowPosY * mArenaWidth) + mArenaWidth;

    for(int i = startPos; i > mArenaWidth; i--)
        mArena[i] = mArena[i - mArenaWidth];

    // blank top row and avoid sides
    for (int x = mArenaWidth - 2; x > 0; x--)
        mArena[x] = BlankChar;

    animate(StackFallAnimationDelayMs);
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
            animate(FlameAnimationSpeedMs);
        }
    }

    for(int y = 0; y < mArenaHeight - 1; y++)
    {
        for(int x = 1; x < mArenaWidth - 1; x++)
        {
            int index = (y * mArenaWidth) + x;
            mArena[index] = BlankChar;
        }
        animate(FlameAnimationSpeedMs - i);
    }
}
