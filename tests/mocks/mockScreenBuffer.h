#pragma once
#include "screenBufferInterface.h"

using namespace screen;

class MockScreenBuffer : public ScreenBufferInterface
{
public:
    void setScreenBufferSize(const int screenHeight, const int screenWidth);
    wchar_t* buffer() override;
    void fillBuffer(const wchar_t c) override;
    void drawToBuffer(const wchar_t* object, int objectHeight, int objectWidth, int xOffset, int yOffset) override;
};
