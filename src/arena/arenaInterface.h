#pragma once

namespace arena
{

class ArenaInterface
{
public:
    virtual void drawCurrentPiece(const wchar_t* piece, int height, int width, int arenaX, int arenaY) = 0;
};

} // namespace arena