#include "score.h"

using namespace score;
using namespace observer;

void Score::draw()
{
    mScreenBuffer.drawToBuffer(box, boxHeight, boxWidth, boxPosX, boxPosY);
    mScreenBuffer.drawToBuffer(title, titleHeight, titleWidth, titlePosX, titlePosY);
    mScreenBuffer.drawToBuffer(mScoreBuffer, scoreHeight, scoreWidth, scorePosX, scorePosY);
}

// void Score::drawToBuffer(const wchar_t* element, const int height, const int width,
//                          const int posX, const int posY)
// {
//     mScreenBuffer.drawToBuffer(element, height, width, posX, posY);
// }



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
