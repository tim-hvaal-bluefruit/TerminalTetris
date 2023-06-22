#include "game.h"

using namespace game;

void Game::initialiseGame()
{
    mArena.createArena();
    mPiece.createNewPiece();
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

bool Game::gameTick()
{
    mTickCount++;
    if(mTickCount == mFallTicks)
    {
        mTickCount = 0;
        if (!dropDown())
        {
            if(!mPiece.createNewPiece())
                return false;
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

    if(mTickCount == defaultNewGameTicks)
    {
        mArena.createArena();
        mTickCount = 0;
        mStackBurned = false;
        return false;
    }

    mTickCount++;
    return true;
}

bool Game::startGame()
{
    mUserInput.getUserInput();
    if(!mUserInput.startGame())
    {
        mArena.addToArena(mArena.getArena(), startGameText, startGameHeight, startGameWidth, textArenaPosX, textArenaPosY);
        mArena.drawArena();
        return false;
    }

    while(!mStackBurned)
    {
        mArena.gameOverFlames();
        mStackBurned = true;
    }

    mStackBurned = false;
    return true;
}
