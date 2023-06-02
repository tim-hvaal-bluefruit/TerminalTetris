#include "mockScreenBuffer.h"
#include <iostream>

using namespace screenBuffer;

void MockScreenBuffer::drawField()
{
    std::cout << "mock draw" << std::endl;
}

wchar_t* MockScreenBuffer::buffer()
{
    return mMockBuffer;
}

void MockScreenBuffer::fillBuffer(const wchar_t c)
{
    for (size_t i = 0; i < (screenHeight * screenWidth); i++)
    {
        mMockBuffer[i] = c;
    }
}