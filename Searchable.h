//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_SEARCHABLE_H
#define EX4_SEARCHABLE_H


#include <vector>
#include <memory>
#include "State.h"
#include "Util.h"

/**
 * Searchable Interface
 * @tparam S the template thar repeasent a node in the graph.
 */
template <typename S>
class Searchable {

protected:
    State<S>* state;

public:
    int nodesEvaluated = 0;
    virtual State<S>* getGoalState() = 0;
    virtual bool isGoalState() = 0;
    virtual bool isGoalState(State<myPoint> dest) = 0;
    virtual std::vector<State<S>*>* getAllPossibleStates() = 0;
    virtual void setAllPossibleStates() = 0;
    virtual void updateState(State<S> *next) = 0;
    virtual bool visited(State<S>* state) = 0;
    virtual void setVisit(State<S>* state) = 0;
    virtual State<S>* getState() = 0;
    virtual ~Searchable(){delete state;}
};

#endif //EX4_SEARCHABLE_H
