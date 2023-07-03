#include "application.h"
#include "instantiation.h"

static Instantiation mInstantiation;

void Application::Loop()
{
    mInstantiation.Loop();
}