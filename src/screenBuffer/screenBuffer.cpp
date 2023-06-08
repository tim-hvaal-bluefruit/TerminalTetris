#include "screenBuffer.h"

using namespace screen;

void ScreenBuffer::setScreenBufferSize(int screenHeight, int screenWidth)
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

void ScreenBuffer::drawToBuffer(const wchar_t* object, int objectHeight, int objectWidth)
{
    for (int x = 0; x < objectWidth; x++)
		for (int y = 0; y < objectHeight; y++)
				mBuffer[y * mScreenWidth + x] = object[y * objectWidth + x];
}
