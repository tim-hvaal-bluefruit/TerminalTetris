#include "windows.h"
#include <iostream>
#include "screenBuffer.h"
#include "console.h"
#include "arena.h"
#include "piece.h"
#include "userInput.h"
#include "game.h"
#include "score.h"

using namespace console;
using namespace arena;
using namespace piece;
using namespace userInput;
using namespace game;
using namespace score;


int main()
{
    // build classes
    Console console;
    ScreenBuffer screenBuffer;
    Arena arena(screenBuffer);
    Piece piece(arena, screenBuffer);
    UserInput userInput(piece);
    Score score(screenBuffer);
    Game game(piece, userInput, arena, score);

    bool programRunning = true;
    bool gameOver = false;

    game.initialiseGame();

    while(programRunning)
    {
        Sleep(50);

        if(!gameOver)
        {
            if (!game.gameTick())
                gameOver = true;
        }
        else
            game.gameOver();

        // copy buffer to console
        console.copyBufferToConsoleBuffer(screenBuffer.buffer(), consoleSize);
    }
}
