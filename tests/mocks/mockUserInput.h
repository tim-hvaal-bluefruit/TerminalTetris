#pragma once
#include "userInputInterface.h"

using namespace userInput;

class MockUserInput : public UserInputInterface
{
public:
    void getUserInput() override;
    void move() override {};
    bool startGame() override;

    bool mStartGamePressed;

private:
    bool mUserInputPolled = false;
};