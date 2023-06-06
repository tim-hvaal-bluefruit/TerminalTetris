#pragma once
#include <iostream>
#include "screenBufferInterface.h"

using namespace screen;

class ScreenBuffer : public ScreenBufferInterface
{
public:
    ScreenBuffer()
    {
        setScreenBufferSize(mScreenHeight, mScreenWidth);
    }

    ScreenBuffer(int screenHeight, int screenWidth)
    {
        mScreenHeight = screenHeight;
        mScreenWidth = screenWidth;
        setScreenBufferSize(mScreenHeight, mScreenWidth);
    }

    void setScreenBufferSize(const int screenHeight, const int screenWidth);
    wchar_t* buffer() override {return mBuffer;}
    void fillBuffer(const wchar_t c) override;
    void drawToBuffer(const char* object, int objectHeight, int objectWidth) override;

// private:
//     wchar_t mBuffer[maxScreenBufferSize];
//     int mScreenHeight;
//     int mScreenWidth;
//     int mBufferSize;
};


// drawtobuffer(char* object, x offset, y offset, height, width)

// loop through x - object width
// loop through y - object height
// (y + offset) * screen width = row position
// (+ x + offset) getx the x position
// buffer[(y + offset * screenWidth) + (x + offset)]
