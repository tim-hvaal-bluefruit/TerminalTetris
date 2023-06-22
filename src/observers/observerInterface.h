#pragma once

namespace observer
{

enum class Event {
    linesCompleted,
    gameOver,
    eventCount
};


class ObserverInterface
{
public:
    virtual void onNotify(Event event, int value) = 0;
};


struct ObserverPair {
    ObserverInterface* entity;
    Event eventType;
};


constexpr int maxObservers = 10;

class Subject
{
public:
    void addObserver(ObserverInterface* entity, Event eventType)
    {
        ObserverPair pair = {entity, eventType};
        mObservers[mNumObservers] = pair;
        mNumObservers++;
    }

    void notify(Event event, int value)
    {
        for(size_t i = 0; i < mNumObservers; i++)
        {
            ObserverPair pair = mObservers[i];
            if (pair.eventType == event)
            {
                pair.entity->onNotify(event, value);
            }
        }
    }

    // getters & setters
    int getNumObservers() {return mNumObservers;}
    ObserverPair* getObservers() {return mObservers;}

private:
    int mNumObservers = 0;
    ObserverPair mObservers[maxObservers];
};

} // namespace event

