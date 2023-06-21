#include "mockConsole.h"

using namespace console;

void MockConsole::animateFrame(const int frameLengthMs, const wchar_t* buffer, const int bufferSize)
{
    mFrameLengthMs = frameLengthMs;
}