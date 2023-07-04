#pragma once
#include "piece.h"
#include "userInput.h"
#include "arena.h"
#include "score.h"
#include "observerInterface.h"

using namespace piece;
using namespace userInput;
using namespace arena;
using namespace score;
using namespace observer;

namespace game
{
    constexpr int defaultFallTicks = 30;
    constexpr int restartGameTicks = 30;

    constexpr int textArenaPosX = 2;
    constexpr int textArenaPosY = 3;

    const wchar_t* const gameOverText = L"GAMEOVER";
    constexpr int gameOverHeight = 1;
    constexpr int gameOverWidth = 8;

    const wchar_t* const startGameText = L"  PRESS     Z   ";
    constexpr int startGameHeight = 2;
    constexpr int startGameWidth = 8;

class Game : public Subject
{
public:
    Game(PieceInterface& piece, UserInputInterface& userInput, ArenaInterface& arena, ScoreInterface& score) :
        mPiece(piece),
        mUserInput(userInput),
        mArena(arena),
        mScore(score),
        mFallTicks(defaultFallTicks)
    {
    }

    void initialiseGame();

    bool gameTick();
    bool menuScreen();
    bool gameInProgress();
    bool gameOver();

    bool dropDown();

    enum class GameState
    {
        MenuScreen,
        GameInProgress,
        GameOver
    };

protected:
    GameState mGameState = GameState::MenuScreen;
    int mTickCount = 0;
    int mFallTicks;
    bool mStackBurned = false;

private:
    PieceInterface& mPiece;
    UserInputInterface& mUserInput;
    ArenaInterface& mArena;
    ScoreInterface& mScore;
};

} // namespace game