#include "mockScreenBuffer.h"
#include <iostream>

using namespace screen;

void MockScreenBuffer::setScreenBufferSize(const int screenHeight, const int screenWidth)
{
    mBufferSize = screenHeight * screenWidth;
    mBuffer[mBufferSize] = L'\0';
}

void MockScreenBuffer::drawToBuffer(const char* object, int objectHeight, int objectWidth)
{
    std::cout << object << " " << objectHeight << " " << objectWidth;
}

void MockScreenBuffer::fillBuffer(const wchar_t c)
{
    for (size_t i = 0; i < mBufferSize; i++)
        mBuffer[i] = c;
}