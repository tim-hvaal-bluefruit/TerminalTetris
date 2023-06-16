#pragma once
#include "pieceInterface.h"

using namespace piece;

class MockPiece : public PieceInterface
{
public:
    void drawCurrentPiece() override;
    void drawPreviewPiece() override;
    void movePiece(moveDirection direction) override;

    bool mMoveLeftCalled = false;
    bool mMoveRightCalled = false;
    bool mMoveDownCalled = false;
};