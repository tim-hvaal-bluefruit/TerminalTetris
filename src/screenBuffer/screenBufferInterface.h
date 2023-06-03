#pragma once
#include <cstddef>

namespace screenBuffer
{
    constexpr size_t screenWidth = 4;
    constexpr size_t screenHeight = 4;

class ScreenBufferInterface
{
public:
    virtual void drawField() = 0;
    virtual wchar_t* buffer() = 0;
    virtual void fillBuffer(const wchar_t c) = 0;
};
} // namespace screen

