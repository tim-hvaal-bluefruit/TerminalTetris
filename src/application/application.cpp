#include "application.h"
#include "instantiation.h"

static Instantiation mInstantiation;

void Application::Init()
{
    mInstantiation.Init();
}

void Application::Loop()
{
    while(true)
    {
        Sleep(50);
        mInstantiation.Game().gameTick();
        mInstantiation.ScreenBuffer().drawAllItems();
        mInstantiation.Console().copyScreenBufferToConsoleBuffer();
    }
}