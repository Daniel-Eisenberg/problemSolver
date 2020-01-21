//
// Created by Yuval Grinberg on 21/01/2020.
//

#ifndef EX3_DFSALGO_H
#define EX3_DFSALGO_H


#include <stack>
#include "queue"
#include "Searcher.h"
#include "Matrix.h"

template <typename T>
class DFSAlgo : public Searcher<T> {
    std::stack<T> stack;
public:
    virtual std::vector<std::string>* search(Searchable<T>* s);
    virtual std::vector<std::string>* backtrace(State<T>* state);
};

template <typename T>
std::vector<std::string>* DFSAlgo<T>::search(Searchable<T> *s) {

    auto v = nullptr;
    s->setVisit(s->getState());
    stack.push(s->getState());

    while (!stack.empty()) {
        s->updateState(stack.pop());
        if (!s->visited(s->getState())) {
            s->setVisit(s->getState());

            for (State<T>* state: s->getAllPossibleStates()) {
                if (state != nullptr && !s->visited(state)) {
                    this->nodesEvaluated++;
                    s->setVisit(state);
                    state->setFather(s);
                    stack.push(state);
                }
            }
        }

        if (stack.size() == 1)
            return this->backtrace(s);
    }
    return v;
}

template <typename T>
std::vector<std::string>* DFSAlgo<T>::backtrace(State<T>* state) {
    auto v = new std::vector<std::string>();
    auto s = state;
    while (s != nullptr) {
        v->push_back(s->getDirection(s->getFather()->getState()));
        s = s.getFather();
    }
    return v;
}

#endif //EX3_DFSALGO_H
