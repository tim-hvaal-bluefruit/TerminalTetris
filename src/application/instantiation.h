#pragma once

#include "windows.h"
#include <iostream>
#include "screenBuffer.h"
#include "console.h"
#include "arena.h"
#include "piece.h"
#include "userInput.h"
#include "game.h"
#include "score.h"
#include "observerInterface.h"

using namespace console;
using namespace arena;
using namespace piece;
using namespace userInput;
using namespace game;
using namespace score;
using namespace observer;

class Instantiation
{
public:
    Instantiation();
    void Loop();

private:
    Console mConsole;
    ScreenBuffer mScreenBuffer;
    Arena mArena;
    Piece mPiece;
    UserInput mUserInput;
    Score mScore;
    Game mGame;
};
