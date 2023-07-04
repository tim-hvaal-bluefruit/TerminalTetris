#pragma once
#include "drawItemInterface.h"

namespace score
{

class ScoreInterface : public screen::DrawItemInterface
{
public:
    // virtual void drawElementsToBuffer() = 0;
    virtual void updateScore(const int increment = 0) = 0;
};

}
