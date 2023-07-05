#pragma once
#include "arena.h"
#include "screenBuffer.h"
#include "pieceInterface.h"
#include <string>

namespace piece
{
class Piece : public PieceInterface
{

public:
    Piece(arena::ArenaInterface& arena, screen::ScreenBufferInterface& screenBuffer);

    // DrawItemInterface
    void draw() override;

    void drawCurrentPiece() override;
    void drawPreviewPiece() override;
    const wchar_t* getPieceData(pieceIndex pieceIdx) {return mPieces[pieceIdx].c_str();}
    bool createNewPiece() override;
    bool movePiece(moveDirection direction) override;
    void addPieceToArena() override;
    int rotateIndex(int x, int y, int width, int height, rotation rotation);
    bool checkPieceFits(int arenaX, int arenaY);
    void rotatePiece(wchar_t* pieceData, pieceIndex piece, rotation rotation, int height, int width);

    // Getters and Setters
    void setCurrentPiece(pieceIndex piece) {mCurrentPiece = piece;}
    pieceIndex getCurrentPiece() {return mCurrentPiece;}

    void setPreviewPiece(pieceIndex piece) {mPreviewPiece = piece;}
    pieceIndex getPreviewPiece() {return mPreviewPiece;}

    void setArenaX(int arenaX) {mArenaX = arenaX;}
    int getArenaX() {return mArenaX;}

    void setArenaY(int arenaY) {mArenaY = arenaY;}
    int getArenaY() {return mArenaY;}

    void setCurrentRotation(rotation rotation) override {mCurrentRotation = rotation;}
    rotation getCurrentRotation() override {return mCurrentRotation;}

private:

    arena::ArenaInterface& mArena;
    screen::ScreenBufferInterface& mScreenBuffer;
    std::wstring mPieces[pieceCount];
    pieceIndex mCurrentPiece;
    rotation mCurrentRotation = r0;
    int mArenaX = 0;
    int mArenaY = 0;

    pieceIndex mPreviewPiece;
};
} // namespace piece
