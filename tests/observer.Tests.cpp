#include <gtest/gtest.h>
#include "observerInterface.h"

using namespace observer;

class MockObserver : public ObserverInterface
{
public:
    void onNotify(Event event, int value) override
    {
        mEvent = event;
        mValue = value;
    }

    Event mEvent;
    int mValue;
};


TEST(ObserverTests, addObserver_increments_num_observers_by_one)
{
    // Given
    Subject subject;
    MockObserver observer;
    ASSERT_EQ(subject.getNumObservers(), 0);

    // When
    subject.addObserver(&observer, Event::linesCompleted);

    // Then
    ASSERT_EQ(subject.getNumObservers(), 1);
}


TEST(ObserverTests, addObserver_adds_observer_and_event_to_observer_list)
{
    // Given
    Subject subject;
    MockObserver observer1;
    MockObserver observer2;

    // When
    subject.addObserver(&observer1, Event::linesCompleted);

    // Then
    ASSERT_EQ(subject.getObservers()[subject.getNumObservers() - 1].entity, &observer1);
    ASSERT_EQ(subject.getObservers()[subject.getNumObservers() - 1].eventType, Event::linesCompleted);

    // When
    subject.addObserver(&observer2, Event::gameOver);

    // Then
    ASSERT_EQ(subject.getObservers()[subject.getNumObservers()].entity, &observer2);
    ASSERT_EQ(subject.getObservers()[subject.getNumObservers()].eventType, Event::linesCompleted);
}