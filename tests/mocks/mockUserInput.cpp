#include "mockUserInput.h"
#include <iostream>

using namespace userInput;

void MockUserInput::getUserInput()
{
    std::cout << "getUserInput() called";
}

void MockUserInput::move()
{
    std::cout << "move() called";
}