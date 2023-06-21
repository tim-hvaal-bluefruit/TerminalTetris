#include "arena.h"

using namespace arena;


void Arena::drawArena()
{
    mScreenBuffer.drawToBuffer(mArena, mArenaHeight, mArenaWidth, mScreenOffsetX, mScreenOffsetY);
}


wchar_t* Arena::createArena()
{
    refreshArena(mArena);
    refreshArena(mActiveArena);
    return mArena;
}


wchar_t* Arena::createArena(int arenaHeight, int arenaWidth)
{
    mArenaHeight = arenaHeight;
    mArenaWidth = arenaWidth;
    refreshArena(mArena);
    refreshArena(mActiveArena);
    return mArena;
}


void Arena::refreshArena(wchar_t* arena)
{
    for(int x = 0; x < mArenaWidth; x++)
    for (int y = 0; y < mArenaHeight; y++)
        arena[y * mArenaWidth + x] = (x == 0 || x == mArenaWidth - 1 || y == mArenaHeight - 1) ? '#' : blankChar;

    arena[mArenaHeight * mArenaWidth] = '\0';
}


void Arena::addToArena(wchar_t* arena, const wchar_t* obj, int height, int width, int arenaX, int arenaY)
{
    int ix, iy;
    for(iy = 0; iy < height; iy++)
    {
        for(ix = 0; ix < width; ix++)
        {
            char c = obj[iy * width + ix];
            if (c != blankChar)
                arena[ ((arenaY + iy) * mArenaWidth) + (arenaX + ix) ] = c;
        }
    }
}

void Arena::drawCurrentPiece(const wchar_t* piece, const int height, const int width, const int arenaX, const int arenaY)
{
    refreshArena(mActiveArena);
    addToArena(mActiveArena, piece, height, width, arenaX, arenaY);
    mScreenBuffer.drawVisibleToBuffer(mActiveArena, mArenaHeight, mArenaWidth, mScreenOffsetX, mScreenOffsetY);
}


bool Arena::checkObjectFits(const wchar_t* obj, int height, int width, int arenaX, int arenaY)
{
    // check arenaX and arenaY are less than mArena height and width
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            char c = obj[y * width + x];
            if (c == blankChar)
                continue;
            if (mArena[((arenaY + y) * mArenaWidth) + (arenaX + x)] != blankChar)
                return false;
        }
    }
    return true;
}

bool Arena::checkLineComplete(int arenaY)
{
    for (int x = 0; x < mArenaWidth; x++)
    {
        const int index = (arenaY * mArenaWidth) + x;
        if (mArena[index] == blankChar)
            return false;
    }
    return true;
}


int Arena::checkAllLines()
{
    int numLines = 0;
    for (int yPos = 0; yPos < mArenaHeight - 1; yPos++) // don't check base
    {
        if (checkLineComplete(yPos))
        {
            numLines++;
        }
    }
    return numLines;
}


// if lines = 0 
//     return lines;

// make event (number of lines)
//     return lines

// who will move the lines down? 
// ... arena! no need for an observer in class surely

// who cares
// ... score cares
// ... audio might care later


// TESTING

// // Given
// create a default arena for testing
// height 8 width 6
// #    # 
// #asdf# line
// #sdf #
// ###### line
// #se gd
// #1234# line
// #!!!!# line
// ###### don't count bottom line

// // when
// int countCompletedLines()

// ASSERT( 4 lines)

// PLAN
// callCheckAllLines
// for each line from bottom to top
//   if line
//     line++
//     animate delete line
//     save line for deletion (list size 4)
//   if no line - continue
//  if lines == 0 - return false
//  call shiftStackDown(list of y coords)

// shiftStackDown
//   takes value of y and moves everything above down by arenaWidth
//   animate could draw the current state - try it
//   takes value of next y and move everything down by arenaWidth
//   takes value of next y and moves down by arenaWidth
//   etc


// observer for score
//   later - lines > 1 raises event
//   score is listening - increases score based on line going down



if line counter >1
// //     send lineCompleteEvent(payload number of lines)
//             // on notify observers run there onNotify function
// //


