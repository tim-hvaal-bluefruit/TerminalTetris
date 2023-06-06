#include "screenBuffer.h"

using namespace screen;

void ScreenBuffer::setScreenBufferSize(const int screenHeight, const int screenWidth)
{
    mScreenHeight = screenHeight;
    mScreenWidth = screenWidth;
    mBufferSize = mScreenHeight * mScreenWidth;

    for(int i = 0; i < mBufferSize; i++)
        mBuffer[i] = '.'; // clear buffer

    mBuffer[mBufferSize] = L'\0'; // null terminate at bounds
}

void ScreenBuffer::fillBuffer(const wchar_t c)
{
    for (int i = 0; i < mBufferSize; i++)
        mBuffer[i] = c;
}

