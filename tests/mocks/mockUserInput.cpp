#include "mockUserInput.h"
#include <iostream>

using namespace userInput;

void MockUserInput::getUserInput()
{
    mUserInputPolled = true;
}

bool MockUserInput::startGame()
{
    if(mUserInputPolled && mStartGamePressed)
        return true;
    return false;
}