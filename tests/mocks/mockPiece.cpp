#include "mockPiece.h"

void MockPiece::drawCurrentPiece()
{
    std::cout << "drawCurrentPiece called" << std::endl;
}

void MockPiece::movePiece(moveDirection direction)
{
    switch (direction)
    {
        case (moveDirection::left):
        {
            mMoveLeftCalled = true;
            break;
        }
        case (moveDirection::right):
        {
            mMoveRightCalled = true;
            break;
        }
        case (moveDirection::down):
        {
            mMoveDownCalled = true;
            break;
        }
    }
}