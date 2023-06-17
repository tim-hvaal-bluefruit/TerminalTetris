#include "mockPiece.h"

void MockPiece::drawCurrentPiece()
{
    std::cout << "drawCurrentPiece called" << std::endl;
}

void MockPiece::drawPreviewPiece()
{
    std::cout << "drawCurrentPiece called" << std::endl;
}

bool MockPiece::movePiece(moveDirection direction)
{
    switch (direction)
    {
        case (moveDirection::left):
        {
            mMoveLeftCalled = true;
            return true;
        }
        case (moveDirection::right):
        {
            mMoveRightCalled = true;
            return true;
        }
        case (moveDirection::down):
        {
            mMoveDownCalled = true;
            return true;
        }
    }
    return false;
}