#include "mockPiece.h"

void MockPiece::drawCurrentPiece()
{}

void MockPiece::drawPreviewPiece()
{}

bool MockPiece::movePiece(moveDirection direction)
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
        case (moveDirection::rotate):
        {
            mRotateCalled = true;
            break;
        }
        default:
            break;
    }
    return mIsMovePossible;
}

void MockPiece::addPieceToArena()
{
    mAddPieceToArenaCalled = true;
}

bool MockPiece::createNewPiece()
{
    return mSpaceForNewPiece;
}

void MockPiece::setCurrentRotation(Rotation rotation)
{
    std::cout << "setCurrentRotation called" << std::endl;
}

Rotation MockPiece::getCurrentRotation()
{
    return Rotation::r0;
}