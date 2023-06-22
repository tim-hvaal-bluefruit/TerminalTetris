#pragma once

namespace userInput
{

class UserInputInterface
{
public:
    virtual void getUserInput() = 0;
    virtual void move() = 0;
    virtual bool startGame() = 0;
};
} // namespace userInput