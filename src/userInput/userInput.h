#pragma once
#include "userInputInterface.h"
#include "piece.h"

using namespace piece;

namespace userInput
{
    enum Key {left = 0, right, down, rotate, keyCount};

class UserInput : public UserInputInterface
{
public:
    UserInput(PieceInterface& piece) : mPiece(piece)
    {}

    void getUserInput() override;
    void move() override;

    // getters and setters
    void setIsKeyPressed(Key key, bool pressed) {mKeysPressed[key] = pressed;}
    bool getIsKeyPressed(Key key) {return mKeysPressed[key];}


private:
    PieceInterface& mPiece;
    bool mKeysPressed[Key::keyCount] = {false};
};
}// namespace UserInput