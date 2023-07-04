#pragma once
#include "consoleInterface.h"
#include "screenBuffer.h"
#include "Windows.h"

namespace console
{
    // default windows console size
    constexpr int consoleWidth = 120;
    constexpr int consoleHeight = 30;
    constexpr int consoleSize = consoleWidth * consoleHeight;

class Console : public ConsoleInterface
{
public:
    Console(screen::ScreenBufferInterface& screenBuffer);

    void copyScreenBufferToConsoleBuffer();
    void copyBufferToConsoleBuffer(const wchar_t* buffer, const int bufferSize) override;
    void animateFrame(const int frameLengthsMs, const wchar_t* buffer, const int bufferSize) override;

private:
    screen::ScreenBufferInterface& mScreenBuffer;
    HANDLE mHConsole;
};

} // namespace console
