#include "instantiation.h"

using namespace console;
using namespace arena;
using namespace piece;
using namespace userInput;
using namespace game;
using namespace score;
using namespace observer;

Instantiation::Instantiation() :
    mArena(mScreenBuffer, mConsole),
    mPiece(mArena, mScreenBuffer),
    mUserInput(mPiece),
    mScore(mScreenBuffer),
    mGame(mPiece, mUserInput, mArena, mScore)
{}

void Instantiation::Loop()
{
    mArena.addObserver(&mScore, Event::linesCompleted);
    mGame.addObserver(&mScore, Event::gameOver);

    bool programRunning = true;
    bool gameRunning = false;
    bool gameOver = false;

    mGame.initialiseGame();


    while(programRunning)
    {
        Sleep(50);

        // start game screen
        if(!gameRunning)
        {
            if(mGame.startGame())
            {
                gameRunning = true;
            }
        }

        // main game
        if(!gameOver && gameRunning)
        {
            if (!mGame.gameTick())
            {
                gameOver = true;
            }
        }

        // game over screen
        if(gameOver)
        {
            if(!mGame.gameOver())
            {
                gameOver = false;
                gameRunning = false;
            }
        }

        mConsole.copyBufferToConsoleBuffer(mScreenBuffer.buffer(), consoleSize);
    }
}