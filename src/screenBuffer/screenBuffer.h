#pragma once
#include <iostream>
#include "screenBufferInterface.h"

using namespace screenBuffer;

class ScreenBuffer : public ScreenBufferInterface
{
public:
    ScreenBuffer(){};
    void drawField() override;
    wchar_t* buffer() override {return mBuffer;}
    void fillBuffer(const wchar_t c) override;

private:
    wchar_t mBuffer[screenWidth * screenHeight];
};