#include "console.h"
#include "screenBuffer.h"

using namespace screenBuffer;

void Console::copyScreenToConsole()
{
    LPDWORD dwBytesWritten = 0;
    wchar_t* scrBuffer = mScreenBuffer.buffer();
    WriteConsoleOutputCharacterW(mHConsole,
                                scrBuffer,
                                (screenHeight * screenWidth),
                                {0,0},
                                dwBytesWritten
    );
}