#pragma once 

#include <iostream>
#include <set>

template <typename T>
class Event {
    public: 
        Event(std::set<T> outcomes);
        Event(std::vector<T> outcomes);

        std::set<T> getOutcomes();
        std::string toString();

    private:
        std::set<T> outcomes_;
};

template <typename T>
class SampleSpace {
    public:
        SampleSpace(int sz);

        Event<T> generateEvent(bool verbose);
        Event<T> generateEvent(int sz, bool verbose);

        Event<T> getUnion(Event<T> eventA, Event<T> eventB, bool verbose);
        Event<T> getIntersection(Event<T> eventA, Event<T> eventB, bool verbose);
        Event<T> getComplement(Event<T> eventA, bool verbose);

        std::string toString();

    private:
        std::set<T> outcomes_;
        std::vector<Event<T>> events_ = {};
};