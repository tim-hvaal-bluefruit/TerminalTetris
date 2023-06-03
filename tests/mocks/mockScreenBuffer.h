#pragma once
#include "screenBufferInterface.h"

using namespace screenBuffer;

class MockScreenBuffer : public ScreenBufferInterface
{
public:

    MockScreenBuffer()
    {
        mMockBuffer[screenWidth * screenHeight - 1] = L'\0';
    }

    void drawField() override;
    wchar_t* buffer() override {return mMockBuffer;}
    void fillBuffer(const wchar_t c) override;

    wchar_t mMockBuffer[screenWidth * screenHeight];
};
