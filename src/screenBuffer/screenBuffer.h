#pragma once
#include <iostream>
#include "screenBufferInterface.h"

using namespace screen;

class ScreenBuffer : public ScreenBufferInterface
{
public:
    ScreenBuffer() :
        mScreenHeight(defaultScreenHeight),
        mScreenWidth(defaultScreenWidth)
    {
        setScreenBufferSize(mScreenHeight, mScreenWidth);
    }

    ScreenBuffer(int screenHeight, int screenWidth) :
        mScreenHeight(screenHeight),
        mScreenWidth(screenWidth)
    {
        setScreenBufferSize(mScreenHeight, mScreenWidth);
    }

    wchar_t* buffer() override {return mBuffer;}

    void setScreenBufferSize(const int screenHeight, const int screenWidth);
    void fillBuffer(const wchar_t c) override;
    void drawToBuffer(const wchar_t* object, int objectHeight, int objectWidth, int xOffset, int yOffset) override;

private:
    int mScreenHeight;
    int mScreenWidth;
    int mBufferSize;
    wchar_t mBuffer[maxScreenBufferSize];
};
