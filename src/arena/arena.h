#pragma once
#include "arenaInterface.h"
#include "screenBuffer.h"
#include "console.h"
#include "observerInterface.h"

using namespace console;
using namespace observer;
using namespace screen;

namespace arena
{
class Arena : public ArenaInterface,
              public Subject
{
public:
    Arena(ScreenBufferInterface& screenBuffer, ConsoleInterface& console );

    // DrawItemInterface
    void draw() override;

    void drawArena();
    void drawCurrentPiece(const wchar_t* piece, int height, int width, int arenaX, int arenaY) override;
    wchar_t* createArena() override;
    wchar_t* createArena(int arenaHeight, int arenaWidth); // for testing convenience - can be nixed later
    void addToArena(wchar_t* arena, const wchar_t* obj, int height, int width, int arenaX, int arenaY);
    bool checkObjectFits(const wchar_t* obj, int height, int width, int arenaX, int arenaY) override;
    void refreshArena(wchar_t* arena);
    int checkAllLines() override;
    bool checkLineComplete(int arenaY);
    void destroyLine(int yPos);
    void animate(int frameLengthMs);
    void moveStackDown(int rowPosY);
    void gameOverFlames();

    // Getters and Setters
    wchar_t* getArena() {return mArena;}
    wchar_t* getActiveArena() {return mActiveArena;}
    int getArenaHeight() {return mArenaHeight;}
    int getArenaWidth() {return mArenaWidth;}

private:
    ScreenBufferInterface& mScreenBuffer;
    ConsoleInterface& mConsole;
    int mArenaHeight;
    int mArenaWidth;
    int mScreenOffsetX;
    int mScreenOffsetY;

    wchar_t mArena[maxArenaSize];
    wchar_t mActiveArena[maxArenaSize];
};
} // namespace arena