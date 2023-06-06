#pragma once

namespace screen
{
    constexpr int defaultScreenHeight = 120;
    constexpr int defaultScreenWidth = 30;
    constexpr int maxScreenBufferSize = 15000;

class ScreenBufferInterface
{
public:
    ScreenBufferInterface() :
        mScreenHeight(defaultScreenHeight),
        mScreenWidth(defaultScreenWidth)
    {}

    virtual void setScreenBufferSize(const int screenHeight, const int screenWidth) = 0;
    virtual wchar_t* buffer() = 0;
    virtual void fillBuffer(const wchar_t c) = 0;
    virtual void drawToBuffer(const char* object, int objectHeight, int objectWidth) = 0;

protected:
    int mScreenHeight;
    int mScreenWidth;
    int mBufferSize;
    wchar_t mBuffer[maxScreenBufferSize];
};
} // namespace screen

