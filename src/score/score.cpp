#include "score.h"

using namespace score;


void Score::drawToBuffer(const wchar_t* element, const int height, const int width,
                         const int posX, const int posY)
{
    mScreenBuffer.drawToBuffer(element, height, width, posX, posY);
}


void Score::drawElementsToBuffer()
{
    drawToBuffer(box, boxHeight, boxWidth, boxPosX, boxPosY);
    drawToBuffer(title, titleHeight, titleWidth, titlePosX, titlePosY);
    drawToBuffer(mScoreBuffer, scoreHeight, scoreWidth, scorePosX, scorePosY);
}


void Score::updateScore(int increment)
{
    mScore += increment;
    size_t bufferLen = sizeof(mScoreBuffer) / sizeof(wchar_t);
    swprintf(mScoreBuffer, bufferLen, L"%d", mScore); // Note swprintf
}


void Score::onNotify(Event event, int value)
{
    if (event != Event::linesCompleted)
        return;

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
