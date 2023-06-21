#pragma once
#include "consoleInterface.h"
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
    Console()
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

    void copyBufferToConsoleBuffer(const wchar_t* buffer, const int bufferSize) override;
    void animateFrame(const int frameLengthsMs, const wchar_t* buffer, const int bufferSize) override;

private:
    HANDLE mHConsole;
};

} // namespace console
