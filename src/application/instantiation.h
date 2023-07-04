#pragma once
#include "windows.h"
#include "screenBuffer.h"
#include "console.h"
#include "arena.h"
#include "piece.h"
#include "userInput.h"
#include "game.h"
#include "score.h"
#include "observerInterface.h"

#include <iostream>

class Instantiation
{
public:
    Instantiation();
    void Init();

    game::Game& Game();
    console::Console& Console();

private:
    console::Console mConsole;
    screen::ScreenBuffer mScreenBuffer;
    arena::Arena mArena;
    piece::Piece mPiece;
    userInput::UserInput mUserInput;
    score::Score mScore;
    game::Game mGame;
};
