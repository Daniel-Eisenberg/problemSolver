//
// Created by Yuval Grinberg on 21/01/2020.
//

#ifndef EX3_BESTFSALGO_H
#define EX3_BESTFSALGO_H

#include "queue"
#include "Searcher.h"
#include "Matrix.h"
#include <set>


template <typename T>
class BestFSAlgo : public Searcher<T> {
    std::priority_queue<T> open_pq;
public:
    virtual std::vector<std::string>* search(Searchable<T>* s);
    virtual std::vector<std::string>* backtrace(State<T>* state);
    virtual T* popOpenList();
    virtual void adujstPriority(T* state);
};


template <typename T>
std::vector<std::string>* BestFSAlgo<T>::search(Searchable<T> *s) {

    auto v = nullptr;
    volatile int bestBacktrace = -1;
    int tempBacktrace = 0;
    set<T> closed;
    s->setVisit(s->getState());
    open_pq.push(s->getState());
    while (!open_pq.empty()) {

        State<T>* n = popOpenList();
        closed.inset(n);
        if (s->isGoalState())
            return this->backtrace(open_pq.front());
        for (State<T>* state: s->getAllPossibleStates()) {
            if (state != nullptr && !(closed.count(state) > 0) && !(open_pq.count(state) > 0)) {
                this->nodesEvaluated++;
                s->setVisit(state);
                state->setFather(s);
                open_pq.push(state);
            } else if (bestBacktrace = -1 || bestBacktrace > this->backtrace(open_pq.front()).size()){
                bestBacktrace = this->backtrace(open_pq.front()).size();
                if (!(open_pq.count(state) > 0))
                    open_pq.push(state);
                else {
                    adujstPriority(state);
                }
            }
        }
    }
}

template <typename T>
std::vector<std::string>* BestFSAlgo<T>::backtrace(State<T>* state) {
    auto v = new std::vector<std::string>();
    auto s = state;
    while (s != nullptr) {
        v->push_back(s->getDirection(s->getFather()->getState()));
        s = s.getFather();
    }
    return v;
}

template <typename T>
T* BestFSAlgo<T>::popOpenList() {
    this->nodesEvaluated++;
    return open_pq.pop();
}

template <typename T>
void BestFSAlgo<T>::adujstPriority(T* state)  {
    auto it = open_pq.find(state);
    open_pq.erase(it);
    open_pq.push(state);
}

#endif //EX3_BESTFSALGO_H
