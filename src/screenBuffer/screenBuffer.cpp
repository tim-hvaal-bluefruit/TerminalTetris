#include "screenBuffer.h"

using namespace screenBuffer;

void ScreenBuffer::drawField()
{
    std::cout << "drawfield called";
}

void ScreenBuffer::fillBuffer(const wchar_t c)
{
    for (int x = 0; x < screenWidth; x++)
        for (int y = 0; y < screenHeight; y++)
            mBuffer[(y*screenWidth) + x] = c;

    mBuffer[screenWidth * screenHeight - 1] = '\0';
}