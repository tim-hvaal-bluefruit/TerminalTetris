#include "console.h"

Console::Console()
{
    mHConsole = CreateConsoleScreenBuffer
                (GENERIC_READ | GENERIC_WRITE,
                 0,
                 NULL,
                 CONSOLE_TEXTMODE_BUFFER,
                 NULL
                );

    SetConsoleActiveScreenBuffer(mHConsole);
}

void Console::drawToConsole(wchar_t* screenBuffer)
{
    LPDWORD dwBytesWritten = 0;
    WriteConsoleOutputCharacter(mHConsole, (LPCSTR)screenBuffer, screenBufferSize, {0,0} , dwBytesWritten);
}