#include "game.h"

using namespace game;


void Game::initialiseGame()
{
    mArena.createArena();
    mPiece.createNewPiece();
}


bool Game::gameTick()
{
    switch (mGameState)
    {
    case GameState::MenuScreen:
        if (!menuScreen())
            mGameState = GameState::GameInProgress;
        break;

    case GameState::GameInProgress:
        if (!gameInProgress())
            mGameState = GameState::GameOver;
        break;

    case GameState::GameOver:
        if (!gameOver())
            mGameState = GameState::MenuScreen;
        break;

    default:
        break;
    }

    return true;
}


bool Game::menuScreen()
{
    mUserInput.getUserInput();
    if(!mUserInput.startGame())
    {
        mArena.addToArena(mArena.getArena(), startGameText, startGameHeight, startGameWidth, textArenaPosX, textArenaPosY);
        mArena.drawArena();
        return true;
    }

    // leave menu screen
    while(!mStackBurned)
    {
        mArena.gameOverFlames();
        mStackBurned = true;
    }
    mStackBurned = false;
    mScore.updateScore();
    return false;
}


bool Game::gameInProgress()
{
    mTickCount++;
    if(mTickCount == mFallTicks)
    {
        mTickCount = 0;
        if (!dropDown())
        {
            if(!mPiece.createNewPiece())
            {
                notify(Event::gameOver, 0);
                return false;
            }
        }
    }

    mUserInput.getUserInput();
    mUserInput.move();

    mArena.drawArena();
    mPiece.drawCurrentPiece();
    mPiece.drawPreviewPiece();

    mScore.drawElementsToBuffer();

    return true;
}


bool Game::dropDown()
{
    if(mPiece.movePiece(moveDirection::down))
    {
        return true;
    }
    mPiece.addPieceToArena();
    mArena.checkAllLines();
    return false;
}


bool Game::gameOver()
{
    while(!mStackBurned)
    {
        mArena.gameOverFlames();
        mStackBurned = true;
        mTickCount = 0;
    }

    mArena.addToArena(mArena.getArena(), gameOverText, gameOverHeight, gameOverWidth, textArenaPosX, textArenaPosY);
    mArena.drawArena();

    if(mTickCount == restartGameTicks)
    {
        mArena.createArena();
        mTickCount = 0;
        mStackBurned = false;
        return false;
    }

    mTickCount++;
    return true;
}
