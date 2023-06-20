#pragma once
#include "pieceInterface.h"

using namespace piece;

class MockPiece : public PieceInterface
{
public:
    void drawCurrentPiece() override;
    void drawPreviewPiece() override;
    bool movePiece(moveDirection direction) override;
    void addPieceToArena() override;
    bool createNewPiece() override;
    void setCurrentRotation(rotation rotation) override;
    rotation getCurrentRotation() override;

    bool mMoveLeftCalled = false;
    bool mMoveRightCalled = false;
    bool mMoveDownCalled = false;
    bool mIsMovePossible = false;
    bool mAddPieceToArenaCalled = false;
    bool mSpaceForNewPiece = true;
};