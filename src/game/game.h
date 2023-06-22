#pragma once
#include "piece.h"
#include "userInput.h"
#include "arena.h"
#include "score.h"

using namespace piece;
using namespace userInput;
using namespace arena;
using namespace score;

namespace game
{
    constexpr int defaultFallTicks = 30;

    constexpr int gameOverHeight = 1;
    constexpr int gameOverWidth = 8;
    constexpr int gameOverArenaPositionX = 2;
    constexpr int gameOverArenaPositionY = 3;

class Game
{
public:
    Game(PieceInterface& piece, UserInputInterface& userInput, ArenaInterface& arena, ScoreInterface& score) :
        mPiece(piece),
        mUserInput(userInput),
        mArena(arena),
        mScore(score),
        mFallTicks(defaultFallTicks)
    {}

    void initialiseGame();
    bool gameTick();
    bool dropDown();
    void gameOver();

    // Getters and Setters
    void setTickCount(int ticks) {mTickCount = ticks;}
    int getTickCount() {return mTickCount;}
    int getFallTicks() {return mFallTicks;}

private:
    PieceInterface& mPiece;
    UserInputInterface& mUserInput;
    ArenaInterface& mArena;
    ScoreInterface& mScore;
    int mTickCount = 0;
    int mFallTicks;
    bool mStackBurned = false;
};
} // namespace game