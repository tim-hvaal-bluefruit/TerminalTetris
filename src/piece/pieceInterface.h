#pragma once
#include <iostream>
#include <cstdlib>
#include <time.h>
#include "drawItemInterface.h"

namespace piece
{
    constexpr int defaultPieceHeight = 4;
    constexpr int defaultPieceWidth = 4;

    enum TetrominoType { p1 = 0, p2, p3, p4, p5, p6, p7, pieceCount };
    enum moveDirection { left = 0, right, down, rotate, directionCount };
    enum rotation { r0 = 0, r90, r180, r270, rotationCount };

class PieceInterface : public screen::DrawItemInterface
{
public:
    virtual void drawCurrentPiece() = 0;
    virtual void drawPreviewPiece() = 0;
    virtual bool movePiece(moveDirection direction) = 0;
    virtual void addPieceToArena() = 0;
    virtual bool createNewPiece() = 0;

// TEMP IN INTERFACE
    virtual void setCurrentRotation(rotation rotation) = 0;
    virtual rotation getCurrentRotation() = 0;
};

} // namespace piece