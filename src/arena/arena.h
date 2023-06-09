#pragma once
#include "screenBuffer.h"

namespace arena
{
    constexpr int defaultArenaHeight = 19;
    constexpr int defaultArenaWidth = 12;
    constexpr int defaultXOffset = 2;
    constexpr int defaultYOffset = 2;
    constexpr int maxArenaSize = 25 * 25; //arena given some free memory (embedded approach)
    constexpr char blankChar = '.';

class Arena
{
public:
    Arena(ScreenBufferInterface& screenBuffer) :
        mScreenBuffer(screenBuffer),
        mArenaHeight(defaultArenaHeight),
        mArenaWidth(defaultArenaWidth),
        mXOffset(defaultXOffset),
        mYOffset(defaultYOffset)
    {}

    void drawArena();
    wchar_t* createArena();
    wchar_t* createArena(int arenaHeight, int arenaWidth, int xOffset, int yOffset);
    wchar_t* getArena() {return mArena;}
    void addToArena(wchar_t* obj, int height, int width, int arenaX, int arenaY);

private:

    ScreenBufferInterface& mScreenBuffer;
    int mArenaHeight;
    int mArenaWidth;
    int mXOffset;
    int mYOffset;

    wchar_t mArena[maxArenaSize];
};
} // namespace arena