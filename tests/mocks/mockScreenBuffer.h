#pragma once
#include "screenBufferInterface.h"

using namespace screen;

class MockScreenBuffer : public ScreenBufferInterface
{
public:
    MockScreenBuffer() :
        mMockBuffer(L"MockBuffer!")
    {}
    void setScreenBufferSize(const int screenHeight, const int screenWidth);
    wchar_t* buffer() override;
    void fillBuffer(const wchar_t c) override;
    void drawToBuffer(const wchar_t* object, int objectHeight, int objectWidth, int xOffset, int yOffset) override;
    void drawVisibleToBuffer(const wchar_t* object, int objectHeight, int objectWidth, int xOffset, int yOffset) override;
    bool registerDrawItem(DrawItemInterface* drawItem) override;
    void drawAllItems() override {};

    // TODO why this ISO forbid error
    wchar_t mMockBuffer[maxScreenBufferSize];
    int mObjectSize;
    int mObjectHeight;
    int mObjectWidth;
    int mObjectXOffset;
    int mObjectYOffset;
    int mCallCount = 0;

    int mNumRegisteredDrawItems = 0;
};
