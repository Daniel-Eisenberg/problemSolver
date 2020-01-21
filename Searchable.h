//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_SEARCHABLE_H
#define EX4_SEARCHABLE_H


#include <vector>
#include "State.h"

template <typename S>
class Searchable {

protected:
    State<S>* state;

public:

    virtual bool isGoalState(State<S> state) = 0;
    virtual std::vector<State<S>*>* getAllPossibleStates() = 0;
    virtual void setAllPossibleStates() = 0;
    virtual void updateState(State<S> *next) = 0;
    virtual bool visited(S* state) = 0;
    virtual void setVisit(State<S>* state) = 0;
    virtual void setFatherstate() = 0;
    virtual State<S>* getState() = 0;
};

#endif //EX4_SEARCHABLE_H
