#include "userInput.h"
#include "windows.h"

using namespace userInput;

void UserInput::getUserInput()
{
    for (int key = 0; key < keyCount; key++)							// R   L   D Z
	    mKeysPressed[key] = (0x8000 & GetAsyncKeyState((unsigned char)("\x25\x27\x28Z"[key]))) != 0;
}

void UserInput::move()
{
    if (mKeysPressed[Key::left])
        mPiece.movePiece(piece::moveDirection::left);

    if (mKeysPressed[Key::right])
        mPiece.movePiece(piece::moveDirection::right);

    if (mKeysPressed[Key::down])
        mPiece.movePiece(piece::moveDirection::down);

    if (mKeysPressed[Key::rotate])
        mPiece.movePiece(piece::moveDirection::rotate);
}