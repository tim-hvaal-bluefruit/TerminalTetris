#include "piece.h"

using namespace piece;

void Piece::drawCurrentPiece(const int arenaX, const int arenaY)
{
    const wchar_t* pieceData = getPieceData(mCurrentPiece);
    mArena.drawCurrentPiece(pieceData, defaultPieceHeight, defaultPieceWidth, arenaX, arenaY);
}