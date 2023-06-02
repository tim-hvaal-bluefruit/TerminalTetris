#pragma once

#include "screenBufferInterface.h"

using namespace screenBuffer;

class MockScreenBuffer : public ScreenBufferInterface
{
public:
    MockScreenBuffer(){};
    void drawField() override;
    wchar_t* buffer() override;
    void fillBuffer(const wchar_t c) override;

    wchar_t mMockBuffer[screenWidth * screenHeight];
};
