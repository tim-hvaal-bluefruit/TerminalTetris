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


int main()
{
    // build classes
    Console console;
    ScreenBuffer screenBuffer;
    Arena arena(screenBuffer, console);
    Piece piece(arena, screenBuffer);
    UserInput userInput(piece);
    Score score(screenBuffer);
    Game game(piece, userInput, arena, score);

    arena.addObserver(&score, Event::linesCompleted);

    bool programRunning = true;
    bool gameRunning = false;
    bool gameOver = false;

    game.initialiseGame();


    while(programRunning)
    {
        Sleep(50);

        // start game screen
        if(!gameRunning)
        {
            if(game.startGame())
            {
                gameRunning = true;
            }
        }

        // main game
        if(!gameOver && gameRunning)
        {
            if (!game.gameTick())
            {
                gameOver = true;
            }
        }

        // game over screen
        if(gameOver)
        {
            if(!game.gameOver())
            {
                gameOver = false;
                gameRunning = false;
            }
        }

        console.copyBufferToConsoleBuffer(screenBuffer.buffer(), consoleSize);
    }
}
