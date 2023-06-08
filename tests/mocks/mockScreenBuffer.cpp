#include "mockScreenBuffer.h"
#include <iostream>

using namespace screen;

void MockScreenBuffer::setScreenBufferSize(const int screenHeight, const int screenWidth)
{
    std::cout << screenHeight << " " << screenWidth;
}

wchar_t* MockScreenBuffer::buffer()
{
    wchar_t* mockBuffer = L"mockBuffer";
    std::cout << "get buffer() called";
}

void MockScreenBuffer::drawToBuffer(const char* object, int objectHeight, int objectWidth)
{
    std::cout << object << " " << objectHeight << " " << objectWidth;
}

void MockScreenBuffer::fillBuffer(const wchar_t c)
{
    std::cout << "fillBuffer() called with :" << c;
}