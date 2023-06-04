#pragma once
#include "screenBuffer.h"

constexpr int arenaHeight = 19;
constexpr int arenaWidth = 12;
constexpr int maxArenaSize = 25 * 25; //arena given some free memory (embedded approach)

class Arena
{
public:
    Arena(ScreenBufferInterface& screenBuffer) : mScreenBuffer(screenBuffer)
    {
    }

    void drawArena();
    char* createArena(int arenaHeight, int arenaWidth);

private:
    ScreenBufferInterface& mScreenBuffer;
    char mArena[maxArenaSize];
};