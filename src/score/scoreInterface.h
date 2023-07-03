#pragma once

namespace score
{

class ScoreInterface
{
public:
    virtual void drawElementsToBuffer() = 0;
    virtual void updateScore(const int increment = 0) = 0;
};

}
