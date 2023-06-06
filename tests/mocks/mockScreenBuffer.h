#pragma once
#include "screenBufferInterface.h"

using namespace screen;

class MockScreenBuffer : public ScreenBufferInterface
{
public:
    MockScreenBuffer()
    {
        setScreenBufferSize(mScreenHeight, mScreenWidth);
    }
    MockScreenBuffer(const int screenHeight, const int screenWidth)
    {
        mScreenHeight = screenHeight;
        mScreenWidth = screenWidth;
        setScreenBufferSize(mScreenHeight, mScreenWidth);
    }

    void setScreenBufferSize(const int screenHeight, const int screenWidth);
    wchar_t* buffer() override {return mBuffer;}
    void fillBuffer(const wchar_t c) override;
    void drawToBuffer(const char* object, int objectHeight, int objectWidth) override;

    // int mMockBufferSize;
    // wchar_t mMockBuffer[maxScreenBufferSize];
};
