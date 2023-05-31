#include "Windows.h"

constexpr size_t screenWidth = 80;
constexpr size_t screenHeight = 30;
constexpr size_t screenBufferSize = screenWidth * screenHeight;

class Console
{
public:
    Console();
    void drawToConsole(wchar_t* screenBuffer);

private:
    HANDLE mHConsole;
};
