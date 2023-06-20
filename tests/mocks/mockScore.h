#pragma once
#include "scoreInterface.h"

using namespace score;

class MockScore : public ScoreInterface
{
public:
    void drawElementsToBuffer() override {}
};