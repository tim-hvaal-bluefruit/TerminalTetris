#include <iostream>
#include <string>
#include "print.h"

int main()
{
    std::string str = "hello, world";
    print(str);
}

// include windows.h

// make a screen buffer  *screen = w_char[80*30];
// fill buffer with blanks
// for (x = 0 -> 80)
//   for (y = 0 -> 30)
//      screen[(y*width) + x] = '0'

// make an active screen buffer
// HANDLE hConsole = CreateConsoleScreenBuffer(read, 0, null, etc) // this is 80 x 30 by default

// set this as the consoles active screen buffer
// setConsoleActiveScreenBuffer(hConsole)

// fill the console with my screen buffer
// DWORD dwBytesWritten = 0; // this gets written to
// consoleOutputCharacter(hConsole, screen, 80*30, starts at, dwBytesWritten)

#include "windows.h"
namespace screen
{

constexpr screen_buffer;
constexpr screen_width;
constexpr screen_height;

class Screen
{
    Screen()
    {
        HANDLE hConsole = CreateConsoleScreenBuffer();//
        setConsoleActiveScreenBuffer(hConsole);
        consoleOutputCharacter(hConsole, screen);
    }

    DWORD mDwBytesWritten = 0;
    wchar_t mScreen[screen_width * screen_height];
}

}