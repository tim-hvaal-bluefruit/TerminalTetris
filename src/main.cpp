#include <iostream>
#include "screenBuffer.h"
#include "console.h"


int main()
{
    ScreenBuffer screenBuffer;
    screenBuffer.fillBuffer(L'Z');
    Console console(screenBuffer);

    int i = 0;
    while(i < 100)
    {
        console.copyScreenToConsole();
        i++;
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

