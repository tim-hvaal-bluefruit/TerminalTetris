#pragma once
#include "piece.h"

using namespace piece;

namespace userInput
{
    enum Key {left = 0, right, down, keyCount};

class UserInput
{
public:
    UserInput(PieceInterface& piece) : mPiece(piece)
    {}

    void getUserInput();
    void move();

    // getters and setters
    void setIsKeyPressed(Key key, bool pressed) {mKeysPressed[key] = pressed;}
    bool getIsKeyPressed(Key key) {return mKeysPressed[key];}


private:
    PieceInterface& mPiece;
    bool mKeysPressed[Key::keyCount] = {false};
};
}// namespace UserInput