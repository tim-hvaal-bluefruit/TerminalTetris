#pragma once
#include "arenaInterface.h"

using namespace arena;

class MockArena : public ArenaInterface
{
public:
    void drawCurrentPiece(const wchar_t* piece, int height, int width, int arenaX, int arenaY) override;
    bool checkObjectFits(const wchar_t* piece, int height, int width, int arenaX, int arenaY) override;
    void addToArena(wchar_t* arena, const wchar_t* piece, int height, int width, int arenaX, int arenaY) override;
    wchar_t* getArena() override;

    wchar_t* mMockArena;
    const wchar_t* mPieceData = L"UNSET_DATA";
    int mPieceHeight= 0;
    int mPieceWidth = 0;
    int mArenaX = 0;
    int mArenaY = 0;
    bool mCheckObjectFitsCalled = false;

    bool mObjectFits = false;
};