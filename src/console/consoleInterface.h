#pragma once

namespace console
{

class ConsoleInterface
{
public:
    virtual void copyBufferToConsoleBuffer(const wchar_t* buffer, const int bufferSize) = 0;
    virtual void animateFrame(const int delayMs, const wchar_t* buffer, const int bufferSize) = 0;
};

} // namespace console
