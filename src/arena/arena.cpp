#include "arena.h"

void Arena::drawArena()
{
}

char* Arena::createArena(int arenaHeight, int arenaWidth)
{
    for(int x = 0; x < arenaWidth; x++)
        for (int y = 0; y < arenaHeight; y++)
            mArena[y * arenaWidth + x] = (x == 0 || x == arenaWidth - 1 || y == arenaHeight - 1) ? '#' : '.';

    mArena[arenaHeight * arenaWidth] = '\0';
    return mArena;
}
