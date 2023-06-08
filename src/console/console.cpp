#include "console.h"

using namespace console;

void Console::copyBufferToConsoleBuffer(const wchar_t* buffer, const int bufferSize)
{
    DWORD dwBytesWritten = 0;
    // wchar_t* screenBuffer = mScreenBuffer.buffer();
    WriteConsoleOutputCharacterW(mHConsole,
                                buffer,
                                bufferSize,
                                {0,0},
                                &dwBytesWritten
    );
}