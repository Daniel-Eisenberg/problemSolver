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

/**
 * DFS algorithm
 * @tparam T node in the graph
 * @param s object that represents the graph
 * @return the way to go from the first node to destenation
 */
template <typename T>
std::vector<std::string>* DFSAlgo<T>::search(Searchable<T> *s) {


    algo_stack.push(s->getState());
    State<myPoint>* goal = nullptr;

    while (!algo_stack.empty()) {
        algo_stack.pop();
        if (!s->visited(s->getState())) {
            s->setVisit(s->getState());

            for (State<T>* state: *s->getAllPossibleStates()) {
                if (state == nullptr || state->getValue() == -1)
                    continue;
                if (!s->visited(state)) {
                    state->setFather(s->getState());
                    algo_stack.push(state);
                }
            }
            if (s->isGoalState())
                goal = s ->getState();

        }
        if (!algo_stack.empty())
            s->updateState(algo_stack.top());
    }

    return this->backtrace(goal);


}

#endif //EX3_DFSALGO_H
