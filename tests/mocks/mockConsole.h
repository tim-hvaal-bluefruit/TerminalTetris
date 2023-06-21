#pragma once
#include "consoleInterface.h"

using namespace console;

class MockConsole : public ConsoleInterface
{
public:
    void copyBufferToConsoleBuffer(const wchar_t* buffer, const int bufferSize) override {};
    void animateFrame(const int frameLengthMs, const wchar_t* buffer, const int bufferSize) override;

    int mFrameLengthMs = 0;
};