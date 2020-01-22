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
    std::stack<State<T>*> algo_stack;
public:
    virtual std::vector<std::string>* search(Searchable<T>* s);
    virtual std::vector<std::string>* backtrace(State<T>* state);
};

template <typename T>
std::vector<std::string>* DFSAlgo<T>::search(Searchable<T> *s) {


    algo_stack.push(s->getState());

    while (!algo_stack.empty()) {
        algo_stack.pop();
        if (!s->visited(s->getState())) {
            s->setVisit(s->getState());

            for (State<T>* state: *s->getAllPossibleStates()) {
                if (state == nullptr || state->getValue() == -1)
                    continue;
                if (!s->visited(state)) {
                    this->nodesEvaluated++;
                    state->setFather(s->getState());
                    algo_stack.push(state);
                }
            }
        }
        s->updateState(algo_stack.top());
    }
    return this->backtrace(s->getState());

}

template <typename T>
std::vector<std::string>* DFSAlgo<T>::backtrace(State<T>* state) {
    auto v = new std::vector<std::string>();
    auto s = state;
    while (s->getFather() != nullptr) {
        v->insert(v->begin(),s->getDirection(s->getFather()->getState()));
        s = s->getFather();
    }
    return v;
}

#endif //EX3_DFSALGO_H
