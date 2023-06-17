#include "game.h"

using namespace game;

void Game::fall()
{
    if(mPiece.movePiece(moveDirection::down))
    {
        mTickCount = 0;
        return;
    }
    mPiece.addPieceToArena();
    
    // increment the piece count
    // call get next piece
    // if you can
        // return
    // if you can't
        // set mGameOver to true

    std::cout << "fall called";
}