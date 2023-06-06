#include "console.h"
#include "screenBuffer.h"

using namespace screen;
using namespace console;

void Console::copyScreenToConsole()
{
    DWORD dwBytesWritten = 0;
    // wchar_t* screenBuffer = mScreenBuffer.buffer();
    WriteConsoleOutputCharacterW(mHConsole,
                                mScreenBuffer.buffer(),
                                console::consoleSize,
                                {0,0},
                                &dwBytesWritten
    );
}