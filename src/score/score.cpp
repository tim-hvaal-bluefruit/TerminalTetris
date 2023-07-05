#include "score.h"

using namespace score;
using namespace observer;


Score::Score(screen::ScreenBufferInterface& screenBuffer)
        : mScreenBuffer(screenBuffer)
{
    mScreenBuffer.registerDrawItem(this);
}


void Score::draw()
{
    mScreenBuffer.drawToBuffer(box, boxHeight, boxWidth, boxPosX, boxPosY);
    mScreenBuffer.drawToBuffer(title, titleHeight, titleWidth, titlePosX, titlePosY);
    mScreenBuffer.drawToBuffer(mScoreBuffer, scoreHeight, scoreWidth, scorePosX, scorePosY);
}


void Score::updateScore(const int increment)
{
    mScore += increment;
    size_t bufferLen = sizeof(mScoreBuffer) / sizeof(wchar_t);

    // note wchar_t library functions
    wmemset(mScoreBuffer, L' ', bufferLen);
    swprintf(mScoreBuffer, bufferLen, L"%d", mScore);
}


void Score::onNotify(Event event, int value)
{
    if (event == Event::eventCount)
        return;

    if (event == Event::linesCompleted)
    {
        switch (value)
        {
            case (1):
                updateScore(oneLinePoints);
                break;
            case (2):
                updateScore(twoLinePoints);
                break;
            case (3):
                updateScore(threeLinePoints);
                break;
            case (4):
                updateScore(fourLinePoints);
                break;
            default:
                break;
        }
    }

    if (event == Event::gameOver)
    {
        setScore(0);
    }
}
