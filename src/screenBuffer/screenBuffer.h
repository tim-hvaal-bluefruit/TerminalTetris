#pragma once
#include <iostream>
#include "screenBufferInterface.h"
#include "drawItemInterface.h"
#include <array>

namespace screen
{

class ScreenBuffer : public ScreenBufferInterface
{
public:
    ScreenBuffer();
    ScreenBuffer(int screenHeight, int screenWidth);

    wchar_t* buffer() override;
    void setScreenBufferSize(const int screenHeight, const int screenWidth);
    void fillBuffer(const wchar_t c) override;
    void drawToBuffer(const wchar_t* object, int objectHeight, int objectWidth, int xOffset, int yOffset) override;
    void drawVisibleToBuffer(const wchar_t* object, int objectHeight, int objectWidth, int xOffset, int yOffset);

    bool registerDrawItem(DrawItemInterface* drawItem);

protected:
    int mNumDrawItems = 0;
    static constexpr int mMaxDrawItems = 10;
    std::array<DrawItemInterface*, mMaxDrawItems> mDrawItems;

private:
    int mScreenHeight;
    int mScreenWidth;
    int mBufferSize;
    wchar_t mBuffer[maxScreenBufferSize];
};

} // namespace screen