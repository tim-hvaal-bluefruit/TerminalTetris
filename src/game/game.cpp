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

    return true;
}

void Game::gameOver()
{
    mArena.addToArena(mArena.getArena(), L"GAMEOVER", gameOverHeight, gameOverWidth, gameOverArenaPositionX, gameOverArenaPositionY);
    mArena.drawArena();
}