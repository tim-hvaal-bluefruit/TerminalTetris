#pragma once

namespace arena
{
    constexpr int defaultArenaHeight = 19;
    constexpr int defaultArenaWidth = 12;

    constexpr int defaultStartPositionX = 4;
    constexpr int defaultStartPositionY = 0;

    constexpr int defaultScreenOffsetX = 2;
    constexpr int defaultScreenOffsetY = 2;

    constexpr int maxArenaSize = 25 * 25; //arena given some free memory (embedded approach)
    constexpr char blankChar = ' ';

class ArenaInterface
{
public:
    virtual void drawCurrentPiece(const wchar_t* piece, int height, int width, int arenaX, int arenaY) = 0;
    virtual bool checkObjectFits(const wchar_t* piece, int height, int width, int arenaX, int arenaY) = 0;
    virtual void addToArena(wchar_t* arena, const wchar_t* piece, int height, int width, int arenaX, int arenaY) = 0;
    virtual wchar_t* getArena() = 0;
    virtual wchar_t* createArena() = 0;
    virtual void drawArena() = 0;
};
} // namespace arena