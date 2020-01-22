//
// Created by Yuval Grinberg on 21/01/2020.
//

#ifndef EX3_DFSALGO_H
#define EX3_DFSALGO_H


#include <stack>
#include "queue"
#include "SspAlgorithm.h"
#include "Matrix.h"

template <typename T>
class DFSAlgo : public SspAlgorithm<T> {
    std::stack<State<T>*> algo_stack;
public:
    virtual std::vector<std::string>* search(Searchable<T>* s);
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

#endif //EX3_DFSALGO_H
