#include "application.h"
#include "instantiation.h"

static Instantiation mInstantiation;

void Application::Init()
{
    mInstantiation.Init();
}

void Application::Run()
{
    mInstantiation.Loop();
}