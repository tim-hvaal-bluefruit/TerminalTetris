#pragma once

namespace observer
{

enum class Event {
    linesCompleted,
    gameOver
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

    // getters & setters
    int getNumObservers() {return mNumObservers;}
    ObserverPair* getObservers() {return mObservers;}

protected:
    int mNumObservers = 0;
    ObserverPair mObservers[maxObservers];
};

} // namespace event

