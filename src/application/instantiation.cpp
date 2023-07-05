#include "instantiation.h"

using namespace console;
using namespace screen;
using namespace arena;
using namespace piece;
using namespace userInput;
using namespace game;
using namespace score;
using namespace observer;

Instantiation::Instantiation() :
    mConsole(mScreenBuffer),
    mArena(mScreenBuffer, mConsole),
    mPiece(mArena, mScreenBuffer),
    mUserInput(mPiece),
    mScore(mScreenBuffer),
    mGame(mPiece, mUserInput, mArena, mScore)
{}

void Instantiation::Init()
{
    mArena.addObserver(&mScore, Event::linesCompleted);
    mGame.addObserver(&mScore, Event::gameOver);

    mGame.initialiseGame();
}

Game& Instantiation::Game()
{
    return mGame;
}

Console& Instantiation::Console()
{
    return mConsole;
}

ScreenBuffer& Instantiation::ScreenBuffer()
{
    return mScreenBuffer;
}