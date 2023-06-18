#pragma once

namespace screen
{
    constexpr int defaultScreenHeight = 30;
    constexpr int defaultScreenWidth = 120;
    constexpr int maxScreenBufferSize = 15000;

class ScreenBufferInterface
{
public:
    virtual void setScreenBufferSize(const int screenHeight, const int screenWidth) = 0;
    virtual wchar_t* buffer() = 0;
    virtual void fillBuffer(const wchar_t c) = 0;
    virtual void drawToBuffer(const wchar_t* object, int objectHeight, int objectWidth, int xOffset, int yOffset) = 0;
    virtual void drawVisibleToBuffer(const wchar_t* object, int objectHeight, int objectWidth, int xOffset, int yOffset) = 0;
};
} // namespace screen

