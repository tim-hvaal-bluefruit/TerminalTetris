#pragma once
#include "observerInterface.h"

using namespace observer;

class MockObserver : public ObserverInterface
{
public:
    void onNotify(Event event, int value) override
    {
        mEvent = event;
        mValue = value;
        mCallCount++;
    }

    Event mEvent = Event::eventCount;
    int mValue = 0;
    int mCallCount = 0;
};