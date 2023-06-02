#include "Windows.h"
#include "screenBufferInterface.h"

using namespace screenBuffer;

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
