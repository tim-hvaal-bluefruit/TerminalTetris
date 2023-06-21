#pragma once
#include "arenaInterface.h"
#include "screenBuffer.h"

namespace arena
{
class Arena : public ArenaInterface
{
public:
    Arena(ScreenBufferInterface& screenBuffer) :
        mScreenBuffer(screenBuffer),
        mArenaHeight(defaultArenaHeight),
        mArenaWidth(defaultArenaWidth),
        mScreenOffsetX(defaultScreenOffsetX),
        mScreenOffsetY(defaultScreenOffsetY)
    {}

    void drawArena();
    void drawCurrentPiece(const wchar_t* piece, int height, int width, int arenaX, int arenaY) override;
    wchar_t* createArena() override;
    wchar_t* createArena(int arenaHeight, int arenaWidth); // for testing convenience - can be nixed later
    void addToArena(wchar_t* arena, const wchar_t* obj, int height, int width, int arenaX, int arenaY);
    bool checkObjectFits(const wchar_t* obj, int height, int width, int arenaX, int arenaY) override;
    void refreshArena(wchar_t* arena);
    bool checkLineComplete(int arenaY);
    int checkAllLines();

    // Getters and Setters
    wchar_t* getArena() {return mArena;}
    wchar_t* getActiveArena() {return mActiveArena;}
    int getArenaHeight() {return mArenaHeight;}
    int getArenaWidth() {return mArenaWidth;}

private:
    ScreenBufferInterface& mScreenBuffer;
    int mArenaHeight;
    int mArenaWidth;
    int mScreenOffsetX;
    int mScreenOffsetY;

    wchar_t mArena[maxArenaSize];
    wchar_t mActiveArena[maxArenaSize];
};
} // namespace arena