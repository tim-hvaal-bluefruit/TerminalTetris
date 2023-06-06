#pragma once
#include "Windows.h"
#include "screenBufferInterface.h"

using namespace screen;
namespace console
{
    // default windows console size
    constexpr int consoleWidth = 120;
    constexpr int consoleHeight = 30;
    constexpr int consoleSize = consoleWidth * consoleHeight;

class Console
{
public:
    Console(ScreenBufferInterface& screenBuffer) :
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

    void copyScreenToConsole();

private:
    HANDLE mHConsole;
    ScreenBufferInterface& mScreenBuffer;
};

} // namespace console
