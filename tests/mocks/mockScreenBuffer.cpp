#include "mockScreenBuffer.h"
#include <iostream>

using namespace screen;

void MockScreenBuffer::setScreenBufferSize(const int screenHeight, const int screenWidth)
{
    std::cout << screenHeight << " " << screenWidth;
}


wchar_t* MockScreenBuffer::buffer()
{
    return mMockBuffer;
}


void MockScreenBuffer::drawToBuffer(const wchar_t* object, int objectHeight, int objectWidth, int xOffset, int yOffset)
{
    mObjectSize = objectHeight * objectWidth;
    mObjectHeight = objectHeight;
    mObjectWidth = objectWidth;
    mObjectXOffset = xOffset;
    mObjectYOffset = yOffset;
    mCallCount++;
}


void MockScreenBuffer::drawVisibleToBuffer(const wchar_t* object, int objectHeight, int objectWidth, int xOffset, int yOffset)
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


bool MockScreenBuffer::registerDrawItem(DrawItemInterface* drawItem)
{
    (void)drawItem;
    mNumRegisteredDrawItems++;
    return true;
};