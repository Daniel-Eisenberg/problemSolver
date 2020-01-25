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
    set<State<T>*> open_pq;
    set<State<T>*> closed;
public:
    virtual std::vector<std::string>* search(Searchable<T>* s);
};

template <typename T>
std::vector<std::string>* BestFSAlgo<T>::search(Searchable<T> *s) {
    int bestBacktrace = -1;
    int tempBacktrace = 0;

    s->setVisit(s->getState());
    open_pq.insert(s->getState());
    while (!open_pq.empty()) {
        State<T>* n = *(min_element(open_pq.begin(), open_pq.end(),
                [] (State<T> *left, State<T> *right) -> bool {
                    return left->getValue() < right->getValue();
                    }));

        if (s->isGoalState(*n)) {
            return this->backtrace(n);
        }

        s->updateState(n);

        for (State<T>* state: *s->getAllPossibleStates()) {
            if (state == nullptr || state->getValue() == -1)
                continue;
            if (!(closed.count(state) > 0) && !(open_pq.count(state) > 0) && !state->visited) {
                s->setVisit(state);
                state->setFather(n);
                open_pq.insert(state);
            }
            else if (bestBacktrace == -1 || bestBacktrace > (tempBacktrace = this->backtrace(state)->size())){
                bestBacktrace = tempBacktrace;
                if (!(open_pq.count(state) > 0)) {
                    open_pq.insert(state);
                }
            }
        }
        open_pq.erase(n);
        closed.insert(n);
    }

    return this->NOT_FOUND;
}

#endif //EX3_BESTFSALGO_H
