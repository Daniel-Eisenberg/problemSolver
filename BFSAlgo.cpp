//
// Created by Daniel Eisenberg on 17/01/2020.
//

#include <string>
#include "BFSAlgo.h"


template <typename T>
std::vector<std::string>* BFSAlgo<T>::search(Searchable<T> *s) {

    auto v = nullptr;
    s->setVisit(s->getState());
    queue.push(s->getState());
    while (!queue.empty()) {

        for (State<T>* state: s->getAllPossibleStates()) {
            if (state != nullptr && !s->visited(state)) {
                s->setVisit(state);
                state->setFather(s);
                queue.push(state);
            }
        }
        //update state
        if (queue.size() == 1)
            v = this->backtrace(queue.front());
        queue.pop();
        s->updateState(queue.front());
    }
    return v;
}

template <typename T>
std::vector<std::string>* BFSAlgo<T>::backtrace(State<T>* state) {
    auto v = new std::vector<std::string>();
    auto s = state;
    while (s != nullptr) {
        v->push_back(s->getDirection(s->getFather()->getState()));
        s = s.getFather();
    }
    return v;
}

