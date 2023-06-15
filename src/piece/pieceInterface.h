#pragma once
#include <iostream>

namespace piece
{
    constexpr int defaultPieceHeight = 4;
    constexpr int defaultPieceWidth = 4;
    enum pieceIndex { p1 = 0, p2, p3, p4, p5, p6, p7, pieceCount};
    enum moveDirection { left = 0, right, down, directionCount};

class PieceInterface
{
public:
    virtual void drawCurrentPiece() = 0;
    virtual void movePiece(moveDirection direction) = 0;
};

} // namespace piece