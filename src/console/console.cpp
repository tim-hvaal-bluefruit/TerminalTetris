#include "console.h"

using namespace console;

Console::Console(screen::ScreenBufferInterface& screenBuffer) :
    mScreenBuffer(screenBuffer)
{
    mHConsole = CreateConsoleScreenBuffer
                (
                    GENERIC_READ | GENERIC_WRITE,
                    0,
                    NULL,
                    CONSOLE_TEXTMODE_BUFFER,
                    NULL
                );

    SetConsoleActiveScreenBuffer(mHConsole);
}

void Console::copyScreenBufferToConsoleBuffer()
{
    copyBufferToConsoleBuffer(mScreenBuffer.buffer(), screen::defaultScreenHeight * screen::defaultScreenWidth);
}

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

void Console::animateFrame(const int frameLengthMs, const wchar_t* buffer, const int bufferSize)
{
    Sleep(frameLengthMs);
    copyBufferToConsoleBuffer(buffer, bufferSize);
}