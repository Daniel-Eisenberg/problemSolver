//
// Created by Yuval Grinberg on 21/01/2020.
//

#ifndef EX3_BESTFSALGO_H
#define EX3_BESTFSALGO_H

#include "queue"
#include "SspAlgorithm.h"
#include "Matrix.h"
#include <set>


template <typename T>
class BestFSAlgo : public SspAlgorithm<T> {
    set<State<T>*> open_nodes;
    set<State<T>*> closed_nodes;
public:
    virtual std::vector<std::string>* search(Searchable<T>* s);
};

/**
 * BestFirstSearch algorithm
 * @tparam T node in the graph
 * @param s object that represents the graph
 * @return the way to go from the first node to destination
 */
template <typename T>
std::vector<std::string>* BestFSAlgo<T>::search(Searchable<T> *s) {
    int tempBacktrace = 0;

    s->setVisit(s->getState());
    open_nodes.insert(s->getState());
    while (!open_nodes.empty()) {
        // Get the node with minimal value from the open set
        State<T>* n = *(min_element(open_nodes.begin(), open_nodes.end(),
                                    [] (State<T> *left, State<T> *right) -> bool {
                                    return left->getAccumulatedValue() < right->getAccumulatedValue();}));

        // If goal state was found return backtrace
        if (s->isGoalState(*n)) {
            return this->backtrace(n);
        }

        // Update the board state to the new node
        s->updateState(n);

        for (State<T>* state: *s->getAllPossibleStates()) {
            // Skip infinity of not possible nodes
            if (state == nullptr || state->getValue() == -1)
                continue;
            if (!(closed_nodes.count(state) > 0) && !(open_nodes.count(state) > 0) && !state->visited) {
                s->setVisit(state);
                state->setFather(n);
                open_nodes.insert(state);
                state->setAccumulatedValue(this->accumulateValue(state));
            }
            // If new best path was found - use it
            else if (state->getAccumulatedValue() > (tempBacktrace = this->accumulateValue(s->getState()) + state->getValue())){
                state->setAccumulatedValue(tempBacktrace);
                if (!(open_nodes.count(state) > 0)) {
                    open_nodes.insert(state);
                }
            }
        }
        open_nodes.erase(n);
        closed_nodes.insert(n);
    }

    return this->NOT_FOUND;
}

#endif //EX3_BESTFSALGO_H
