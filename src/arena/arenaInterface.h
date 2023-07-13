#pragma once
#include "drawItemInterface.h"
#include "tetromino.h"

namespace arena
{
    static constexpr int ArenaDisplayOffsetX = 5;
    static constexpr int ArenaDisplayOffsetY = 2;
    static constexpr int DefaultArenaHeight = 19;
    static constexpr int DefaultArenaWidth = 12;
    static constexpr int MaxArenaSize = 25 * 25; //arena given some free memory (embedded approach)

    static constexpr int TetrominoStartPositionX = 4;
    static constexpr int TetrominoStartPositionY = 0;
    static constexpr int MaxObjectSize = 17;
    static constexpr tetromino::TetrominoType DefaultTetromino = tetromino::TetrominoType::t1;

    static constexpr char BlankChar = ' ';

    static constexpr int DestroyLineAnimationSpeedMs = 15;
    static constexpr int StackFallAnimationDelayMs = 130;
    static constexpr int FlameAnimationSpeedMs = 13;


class ArenaInterface : public screen::DrawItemInterface
{
public:
    virtual void drawCurrentPiece(const wchar_t* piece, int height, int width, int arenaX, int arenaY) = 0;
    virtual bool checkObjectFits(const wchar_t* piece, int height, int width, int arenaX, int arenaY) = 0;
    virtual void addToArena(wchar_t* arena, const wchar_t* piece, int height, int width, int arenaX, int arenaY) = 0;
    virtual wchar_t* getArena() = 0;
    virtual wchar_t* createArena() = 0;
    virtual void drawArena() = 0;
    virtual int checkAllLines() = 0;
    virtual void gameOverFlames() = 0;
    virtual void draw() = 0;
};
} // namespace arena