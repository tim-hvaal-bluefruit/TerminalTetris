#pragma once
#include "arenaInterface.h"

using namespace arena;

class MockArena : public ArenaInterface
{
public:
    void drawCurrentPiece(const wchar_t* piece, int height, int width, int arenaX, int arenaY) override;
    bool checkObjectFits(const wchar_t* piece, int height, int width, int arenaX, int arenaY) override;
    void addToArena(wchar_t* arena, const wchar_t* piece, int height, int width, int arenaX, int arenaY) override;
    wchar_t* getArena() override {return mMockArena;}
    wchar_t* createArena() override {return mMockArena;}
    void drawArena() override {};
    void copyToMockObject(const wchar_t* object, int height, int width);
    int checkAllLines() override {return 0;};
    void gameOverFlames() override {};

    wchar_t* mMockArena;
    wchar_t mObjectData[maxObjectSize];
    int mObjectHeight= 0;
    int mObjectWidth = 0;
    int mArenaX = 0;
    int mArenaY = 0;
    bool mCheckObjectFitsCalled = false;

    bool mObjectFits = false;
};