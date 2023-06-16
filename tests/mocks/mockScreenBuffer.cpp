#include "mockScreenBuffer.h"
#include <iostream>

using namespace screen;

void MockScreenBuffer::setScreenBufferSize(const int screenHeight, const int screenWidth)
{
    std::cout << screenHeight << " " << screenWidth;
}

wchar_t* MockScreenBuffer::buffer()
{
    std::cout << "get buffer() called";
    return mMockBuffer;
}

void MockScreenBuffer::drawToBuffer(const wchar_t* object, int objectHeight, int objectWidth, int xOffset, int yOffset)
{
    mObjectSize = objectHeight * objectWidth;
    mObjectHeight = objectHeight;
    mObjectWidth = objectWidth;
    mObjectXOffset = xOffset;
    mObjectYOffset = yOffset;
}

void MockScreenBuffer::fillBuffer(const wchar_t c)
{
    std::cout << "fillBuffer() called with :" << c;
}