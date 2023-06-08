#include "windows.h"
#include <iostream>
#include "screenBuffer.h"
#include "console.h"
#include "arena.h"

using namespace console;

int main()
{
    Console console;
    ScreenBuffer screenBuffer;
    // Arena arena(screenBuffer);

    // arena.createArena(arenaHeight, arenaWidth);

    const int objectHeight1 = 3, objectWidth1 = 3, xOffset1 = 1, yOffset1 = 1;
    const wchar_t* object1 = L"#.#"
                              "#.#"
                              "###";

    const int objectHeight2 = 1, objectWidth2 = 5, xOffset2 = 10, yOffset2 = 1;
    const wchar_t* object2 = L"SCORE";

    const int objectHeight3 = 1, objectWidth3 = 3, xOffset3 = 11, yOffset3 = 2;
    const wchar_t* object3 = L"123";

    while(true)
    {
        screenBuffer.drawToBuffer(object1, objectHeight1, objectWidth1, xOffset1, yOffset1);
        screenBuffer.drawToBuffer(object2, objectHeight2, objectWidth2, xOffset2, yOffset2);
        screenBuffer.drawToBuffer(object3, objectHeight3, objectWidth3, xOffset3, yOffset3);
        console.copyBufferToConsoleBuffer(screenBuffer.buffer(), consoleSize);
    }
}





// WORKING PROTOTYPE
// int nScreenWidth = 120;
// int nScreenHeight = 40;
// int main()
// {
//     char screen[nScreenWidth*nScreenHeight];
//     HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
//     SetConsoleActiveScreenBuffer(hConsole);
//     DWORD dwBytesWritten = 0;
//     while(1)
//     {
//         for (size_t i = 0; i < (120 * 29) + 1; i++)
//             screen[i] = '!';
//         screen[nScreenWidth * nScreenHeight - 1] = '\0';
//     	WriteConsoleOutputCharacter(hConsole, (LPCSTR)screen, 120 * 29 + 20, { 0,0 }, &dwBytesWritten);
//     }
// }

