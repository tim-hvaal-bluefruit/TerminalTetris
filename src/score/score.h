#pragma once
#include "scoreInterface.h"
#include "screenBuffer.h"

namespace score
{
    const wchar_t* const box = L"#################"
                                "#               #"
                                "#               #"
                                "#               #"
                                "#               #"
                                "#################";
    constexpr int boxHeight = 6;
    constexpr int boxWidth = 17;
    constexpr int boxPosX = 30;
    constexpr int boxPosY = 2;

    const wchar_t* const title =  L"S C O R E";
    constexpr int titleHeight = 1;
    constexpr int titleWidth = 9;
    constexpr int titlePosX = boxPosX + 4;
    constexpr int titlePosY = boxPosY + 2;

    constexpr int scoreHeight = 1;
    constexpr int scoreWidth = 5;
    constexpr int scorePosX = boxPosX + 8;
    constexpr int scorePosY = boxPosY + 3;


class Score : public ScoreInterface
{
public:
    Score(ScreenBufferInterface& screenBuffer)
        : mScreenBuffer(screenBuffer) {}

    void drawToBuffer(const wchar_t* element, const int height, const int width,
                      const int posX, const int posY);
    void drawElementsToBuffer() override;
    void updateScore(const int increment);

    // Getters and Setters
    int getScore() {return mScore;}
    void setScore(int score) {mScore = score;}
    wchar_t* getScoreBuffer() {return mScoreBuffer;}

private:
    ScreenBufferInterface& mScreenBuffer;
    int mScore = 0;
    wchar_t mScoreBuffer[scoreWidth + 1] = L"0";
};

} // namespace score