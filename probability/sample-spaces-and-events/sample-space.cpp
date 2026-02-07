#include <iostream>
#include <algorithm>
#include <random>
#include <set>
#include <sample-space.hpp>

template <typename T>
Event<T>::Event(std::set<T> outcomes) {
    outcomes_ = outcomes;
}

template<typename T>
Event<T>::Event(std::vector<T> outcomes) {
    outcomes_ = std::set<T> {};
    for (T outcome : outcomes) {
        outcomes_.insert(outcome);
    }
}

template<typename T>
std::set<T> Event<T>::getOutcomes() {
    return outcomes_;
}

std::string Event<int>::toString() {
    std::string outputString = "";
    for (int outcome: outcomes_) {
        outputString += outcome + " ";
    }

    return outputString;
}

SampleSpace<int>::SampleSpace(int sz){
        for (int i = 0; i < outcomes_.size(); i++) {
            int randomOutcome = rand() % outcomes_.size() * 2; // keep possible values within a range
            while (outcomes_.contains(randomOutcome)) {
                randomOutcome = rand() % outcomes_.size();
            }

            outcomes_.insert(randomOutcome);
        }
    }

Event<int> SampleSpace<int>::generateEvent(bool verbose=true) {
    int eventSize = rand() % (outcomes_.size() - 1);

    return generateEvent(eventSize, verbose);
}

Event<int> SampleSpace<int>::generateEvent(int sz, bool verbose=true) {
    std::vector<int> eventVector;

    // setting up the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // sample from the outcomes
    std::sample(
        outcomes_.begin(),
        outcomes_.end(),
        std::back_insert_iterator(eventVector),
        sz,
        gen
    );

    if (verbose) {
        std::cout << "Sampled elements: ";
        for (int element : eventVector) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    Event<int> event = Event(eventVector);
    events_.push_back(event);
    return event;
}

Event<int> SampleSpace<int>::getUnion(Event<int> eventA, Event<int> eventB, bool verbose=true) {
    std::set<int> outcomesA = eventA.getOutcomes();
    std::set<int> outcomesB =  eventB.getOutcomes();

    if (verbose) {
        std::cout << "Event A: " << eventA.toString();
        std::cout << "Event B: " << eventB.toString();
    }

    for (int outcome : outcomesB) {
        outcomesA.insert(outcome);
    }

    Event<int> outputEvent = Event(outcomesA);

    if (verbose) {
        std::cout << "Union: " << outputEvent.toString(); 
    }

    return outputEvent;
}

Event<int> SampleSpace<int>::getIntersection(Event<int> eventA, Event<int> eventB, bool verbose=true) {
    std::set<int> intersectionSet = {};

    if (verbose) {
        std::cout << "Event A: " << eventA.toString();
        std::cout << "Event B: " << eventB.toString();
    }

    for (int outcome : eventA.getOutcomes()) {
        if (eventB.getOutcomes().contains(outcome)) {
            intersectionSet.insert(outcome);
        }
    }

    Event<int> outputEvent = Event(intersectionSet);

    if (verbose) {
        std::cout << "Intersection: " << outputEvent.toString();
    }
}

Event<int> SampleSpace<int>::getComplement(Event<int> event, bool verbose=true) {
    std::set<int> complementSet = {};

    if (verbose) {
        std::cout << "Sample Space: " << toString();
        std::cout << "Event: " << event.toString();
    }

    std::set<int> eventOutcomes = event.getOutcomes();
    for (int outcome : outcomes_) {
        if (!eventOutcomes.contains(outcome)) {
            complementSet.insert(outcome);
        }
    }

    if (verbose) {
        std::cout << "Complement: " << event.toString();
    }

    return complementSet;
}

std::string SampleSpace<int>::toString() {
    std::string outputString = "";
    for (int outcome : outcomes_) {
        outputString += outcome + " ";
    }

    return outputString;
}