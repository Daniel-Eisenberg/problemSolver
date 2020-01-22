//
// Created by Daniel Eisenberg on 17/01/2020.
//

#ifndef EX4_BFS_H
#define EX4_BFS_H

#include "queue"
#include "Searcher.h"
#include "Searchable.h"
#include "Matrix.h"
#include "Util.h"
template <typename T>
class BFS : public Searcher<T> {
    std::queue<State<T>*> bfs_queue;
public:
    virtual std::vector<std::string>* search(Searchable<T>* s);
    virtual std::vector<std::string>* backtrace(State<T>* state);
};

template <typename T>
std::vector<std::string>* BFS<T>::search(Searchable<T> *s) {

    s->setVisit(s->getState());
    bfs_queue.push(s->getState());

    while (!bfs_queue.empty()) {

        for (State<T>* state : *s->getAllPossibleStates()) {
            if (state != nullptr && !s->visited(state)) {
                s->setVisit(state);
                state->setFather(s->getState());
                bfs_queue.push(state);
            }
        }
        //update state
        if (s->isGoalState())
            return this->backtrace(bfs_queue.front());
        bfs_queue.pop();
        s->updateState(bfs_queue.front());
    }
}

template <typename T>
std::vector<std::string>* BFS<T>::backtrace(State<T>* state) {
    auto v = new std::vector<std::string>();
    auto s = state;
    while (s->getFather() != nullptr) {
        v->insert(v->begin(),s->getDirection(s->getFather()->getState()));
        s = s->getFather();
    }
    return v;
}

#endif //EX4_BFS_H
