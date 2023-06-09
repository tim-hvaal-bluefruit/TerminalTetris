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
    const wchar_t* getPieceData(TetrominoType pieceIdx) {return mPieces[pieceIdx].c_str();}
    bool createNewPiece() override;
    bool movePiece(moveDirection direction) override;
    void addPieceToArena() override;
    int rotateIndex(int x, int y, int width, int height, rotation rotation);
    bool checkPieceFits(int arenaX, int arenaY);
    void rotatePiece(wchar_t* pieceData, TetrominoType piece, rotation rotation, int height, int width);

    // Getters and Setters
    void setCurrentPiece(TetrominoType piece) {mCurrentPiece = piece;}
    TetrominoType getCurrentPiece() {return mCurrentPiece;}

    void setPreviewPiece(TetrominoType piece) {mPreviewPiece = piece;}
    TetrominoType getPreviewPiece() {return mPreviewPiece;}

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
    TetrominoType mCurrentPiece;
    rotation mCurrentRotation = r0;
    int mArenaX = 0;
    int mArenaY = 0;

    TetrominoType mPreviewPiece;
};


// class Tetromino
// {
// public:
//     Tetromino(int )

// private:
//     static constexpr int tetrominoHeight = 4;
//     int mArenaX;
//     int mArenaY;
//     TetrominoType mType;
//     rotation mRotation;
// };


} // namespace piece


// next - rename pieceIndex to pieceType
// make tetromino class (to replace piece)
// 