#pragma once
#include "scoreInterface.h"

using namespace score;

class MockScore : public ScoreInterface
{
public:
    // void drawElementsToBuffer() override {}
    void updateScore(const int increment) override {(void)increment; callCount++;}
    void draw() override {mDrawCallCount++;};

    int callCount = 0;
    int mDrawCallCount = 0;
};
