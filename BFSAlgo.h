//
// Created by Daniel Eisenberg on 17/01/2020.
//

#ifndef EX4_BFS_H
#define EX4_BFS_H

#include "queue"
#include "SspAlgorithm.h"
#include "Searchable.h"
#include "Matrix.h"
#include "Util.h"
template <typename T>
class BFS : public SspAlgorithm<T>  {
    std::queue<State<T>*> bfs_queue;
public:
    virtual std::vector<std::string>* search(Searchable<T>* s);
};

template <typename T>
std::vector<std::string>* BFS<T>::search(Searchable<T> *s) {

    s->setVisit(s->getState());
    bfs_queue.push(s->getState());

    while (!bfs_queue.empty()) {

        for (State<T>* state : *s->getAllPossibleStates()) {
            if (state == nullptr || state->getValue() == -1)
                continue;
            if (!s->visited(state)) {
                s->setVisit(state);
                state->setFather(s->getState());
                bfs_queue.push(state);
            }
        }
        bfs_queue.pop();
        s->updateState(bfs_queue.front());
    }
    //update state
    return this->backtrace(bfs_queue.front());
}

#endif //EX4_BFS_H
