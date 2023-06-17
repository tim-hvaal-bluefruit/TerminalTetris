#pragma once
#include "piece.h"

using namespace piece;

namespace game
{
class Game
{
public:
    Game(PieceInterface& piece) :
        mPiece(piece)
    {}
    void fall();

    // Getters and Setters
    void incrementTickCount() {mTickCount++;}
    int getTickCount() {return mTickCount;}

private:
    PieceInterface& mPiece;
    int mTickCount = 0;

};
} // namespace game