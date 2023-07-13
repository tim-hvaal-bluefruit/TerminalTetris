#pragma once
// #include "piece.h"
#include "arenaInterface.h"
#include "console.h"
#include "observerInterface.h"
#include "screenBuffer.h"

namespace arena
{
class Arena : public ArenaInterface,
              public observer::Subject
{
public:
    Arena(screen::ScreenBufferInterface& screenBuffer, console::ConsoleInterface& console);

    // DrawItemInterface
    void draw() override;

    // ArenaInterface
    void drawCurrentPiece(const wchar_t* piece, int height, int width, int arenaX, int arenaY) override;
    wchar_t* createArena() override;
    wchar_t* getArena() override;
    bool checkObjectFits(const wchar_t* obj, int height, int width, int arenaX, int arenaY) override;
    int checkAllLines() override;

    void drawArena();
    wchar_t* createArena(int arenaHeight, int arenaWidth); // for testing
    void addToArena(wchar_t* arena, const wchar_t* obj, int height, int width, int arenaX, int arenaY);
    void refreshArena(wchar_t* arena);
    bool checkLineComplete(int arenaY);
    void destroyLine(int yPos);
    void animate(int frameLengthMs);
    void moveStackDown(int rowPosY);
    void gameOverFlames();

protected:
    tetromino::Tetromino mCurrentPiece;
    int mArenaHeight;
    int mArenaWidth;
    wchar_t mArena[MaxArenaSize];
    wchar_t mActiveArena[MaxArenaSize];

private:
    screen::ScreenBufferInterface& mScreenBuffer;
    console::ConsoleInterface& mConsole;
};
} // namespace arena