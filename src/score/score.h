#pragma once
#include <string.h>
#include "scoreInterface.h"
#include "screenBuffer.h"
#include "observerInterface.h"


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

    constexpr int oneLinePoints = 10;
    constexpr int twoLinePoints = 20;
    constexpr int threeLinePoints = 40;
    constexpr int fourLinePoints = 80;


class Score : public score::ScoreInterface,
              public observer::ObserverInterface
{
public:
    Score(screen::ScreenBufferInterface& screenBuffer);

    // ScoreInterface
    void updateScore(const int increment = 0) override;

    // DrawItemInterface (via ScoreInterface)
    void draw() override;

    // ObserverInterface
    void onNotify(observer::Event event, int value) override;


    // Getters and Setters
    int getScore() {return mScore;}
    void setScore(int score) {mScore = score;}
    wchar_t* getScoreBuffer() {return mScoreBuffer;}


private:
    screen::ScreenBufferInterface& mScreenBuffer;
    int mScore = 0;
    wchar_t mScoreBuffer[scoreWidth + 1] = L"0";
};

} // namespace score