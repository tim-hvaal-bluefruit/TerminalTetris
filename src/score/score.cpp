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
