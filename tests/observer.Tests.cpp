#include <gtest/gtest.h>
#include "observerInterface.h"
#include "mockObserver.h"

using namespace observer;

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
    ASSERT_EQ(subject.getObservers()[subject.getNumObservers() - 1].entity, &observer2);
    ASSERT_EQ(subject.getObservers()[subject.getNumObservers() - 1].eventType, Event::gameOver);
}


TEST(observerTests, notify_calls_onNotify_for_each_observer)
{
    // Given
    Subject subject;
    MockObserver observer1;
    MockObserver observer2;
    subject.addObserver(&observer1, Event::linesCompleted);
    subject.addObserver(&observer2, Event::linesCompleted);
    int numLines;

    // When
    subject.notify(Event::linesCompleted, numLines);

    // Then
    ASSERT_EQ(observer1.mCallCount, 1);
    ASSERT_EQ(observer2.mCallCount, 1);
}