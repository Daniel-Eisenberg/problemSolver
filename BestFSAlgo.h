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
    std::priority_queue<State<T>*> open_pq;
public:
    virtual std::vector<std::string>* search(Searchable<T>* s);
    virtual std::vector<std::string>* backtrace(State<T> state);
    virtual State<T>* popOpenList();
    virtual void adujstPriority(State<T>* state);
    bool inQueue(State<T>* state);
};


template <typename T>
std::vector<std::string>* BestFSAlgo<T>::search(Searchable<T> *s) {

    auto v = nullptr;
    volatile int bestBacktrace = -1;
    int tempBacktrace = 0;
    set<State<T>*> closed;
    s->setVisit(s->getState());
    open_pq.push(s->getState());
    while (!open_pq.empty()) {

        State<T>* n = popOpenList();
        closed.insert(n);
        if (s->isGoalState())
            return this->backtrace(*open_pq.top());

        for (State<T>* state: *s->getAllPossibleStates()) {
            if (state == NULL)
                continue;
            if (!(closed.count(state) > 0) && !this->inQueue(state)) {
                this->nodesEvaluated++;
                s->setVisit(state);
                state->setFather(s->getState());
                open_pq.push(state);
            } else if (bestBacktrace == -1 || bestBacktrace > this->backtrace(*open_pq.top())->size()){
                bestBacktrace = this->backtrace(*open_pq.top())->size();
                if (!this->inQueue(state))
                    open_pq.push(state);
//                else {
//                    adujstPriority(state);
//                }
            }
        }
    }
}

template <typename T>
std::vector<std::string>* BestFSAlgo<T>::backtrace(State<T> state) {
    auto v = new std::vector<std::string>();
    auto s = state;
    while (s->getFather() != nullptr) {
        v->insert(v->begin(),s->getDirection(s->getFather()->getState()));
        s = s->getFather();
    }
    return v;
}

template <typename T>
State<T>* BestFSAlgo<T>::popOpenList() {
    this->nodesEvaluated++;
    auto tmp = open_pq.top();
    open_pq.pop();
    return tmp;
}

template <typename T>
void BestFSAlgo<T>::adujstPriority(State<T>* state)  {
    vector<State<T>*> v;
    while (open_pq.top() != state) {
        v.push_back(open_pq.top());
        open_pq.pop();
    }
    open_pq.pop();
    while (!v.empty()) {
        open_pq.push(v.at(0));
        v.erase(v.begin());
    }
    open_pq.push(state);
}

template <typename T>
bool BestFSAlgo<T>::inQueue(State<T> *state) {
    bool i = true;
    vector<State<T>*> v;
    while (!open_pq.empty() &&open_pq.top() != state) {
        v.push_back(open_pq.top());
        open_pq.pop();
    }
    if (open_pq.empty()) {
        i = false;
    }
    while (!v.empty()) {
        open_pq.push(v.at(0));
        v.erase(v.begin());
    }
    return i;
}



#endif //EX3_BESTFSALGO_H
