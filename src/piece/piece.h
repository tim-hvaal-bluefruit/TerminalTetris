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
    int rotateIndex(int x, int y, int width, int height, Rotation rotation);
    bool checkPieceFits(int arenaX, int arenaY);
    void rotatePiece(wchar_t* pieceData, TetrominoType piece, Rotation rotation, int height, int width);

    // Getters and Setters
    void setCurrentPiece(TetrominoType piece) {mCurrentPiece = piece;}
    TetrominoType getCurrentPiece() {return mCurrentPiece;}

    void setPreviewPiece(TetrominoType piece) {mPreviewPiece = piece;}
    TetrominoType getPreviewPiece() {return mPreviewPiece;}

    void setArenaX(int arenaX) {mArenaX = arenaX;}
    int getArenaX() {return mArenaX;}

    void setArenaY(int arenaY) {mArenaY = arenaY;}
    int getArenaY() {return mArenaY;}

    void setCurrentRotation(Rotation rotation) override {mCurrentRotation = rotation;}
    Rotation getCurrentRotation() override {return mCurrentRotation;}

private:
    arena::ArenaInterface& mArena;
    screen::ScreenBufferInterface& mScreenBuffer;
    std::wstring mPieces[pieceCount];
    TetrominoType mCurrentPiece;
    Rotation mCurrentRotation = r0;
    int mArenaX = 0;
    int mArenaY = 0;

    TetrominoType mPreviewPiece;
};
} // namespace piece

namespace tetromino
{
    static constexpr int TetrominoHeight = 4;
    static constexpr int TetrominoWidth = 4;
    static constexpr int TetrominoSize = TetrominoHeight * TetrominoWidth;
    static constexpr piece::Rotation StartRotation = piece::Rotation::r0;

struct TetrominoData
{
    std::wstring mTetrominoData[piece::TetrominoType::pieceCount];
    TetrominoData()
    {
        mTetrominoData[piece::TetrominoType::t1].append(L"  X "
                                                         "  X "
                                                         "  X "
                                                         "  X ");

        mTetrominoData[piece::TetrominoType::t2].append(L"  X "
                                                         " XX "
                                                         "  X "
                                                         "    ");

        mTetrominoData[piece::TetrominoType::t3].append(L"    "
                                                         " XX "
                                                         " XX "
                                                         "    ");

        mTetrominoData[piece::TetrominoType::t4].append(L"  X "
                                                         " XX "
                                                         " X  "
                                                         "    ");

        mTetrominoData[piece::TetrominoType::t5].append(L" X  "
                                                         " XX "
                                                         "  X "
                                                         "    ");

        mTetrominoData[piece::TetrominoType::t6].append(L" X  "
                                                         " X  "
                                                         " XX "
                                                         "    ");

        mTetrominoData[piece::TetrominoType::t7].append(L"  X "
                                                         "  X "
                                                         " XX "
                                                         "    ");
    }
};


class Tetromino
{
public:
    Tetromino(TetrominoData& data, piece::TetrominoType type, int posX, int posY);
    int rotateIndex(int x, int y, int width, int height, piece::Rotation rotation);
    void rotatePiece(wchar_t* data, piece::TetrominoType type, piece::Rotation rotation, int height, int width);

    // Get
    const wchar_t* Data(piece::TetrominoType type);
    piece::TetrominoType Type();
    piece::Rotation Rotation();
    int PosX();
    int PosY();

    // Set
    void SetType(piece::TetrominoType type);
    void SetRotation(piece::Rotation rotation);
    void SetPosX(int arenaX);
    void SetPosY(int arenaY);

protected:
    piece::TetrominoType mType;
    piece::Rotation mRotation = StartRotation;
    int mPosX;
    int mPosY;

private:
    TetrominoData& mData;
};

} // namespace tetromino
