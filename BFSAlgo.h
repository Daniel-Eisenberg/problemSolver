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
class BFSAlgo : public SspAlgorithm<T>  {
    std::queue<State<T>*> bfs_queue;
public:
    virtual std::vector<std::string>* search(Searchable<T>* s);
};
/**
 * BFSAlgo algorithm
 * @tparam T node in the graph
 * @param s object that represents the graph
 * @return the way to go from the first node to destination
 */
template <typename T>
std::vector<std::string>* BFSAlgo<T>::search(Searchable<T> *s) {

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
        if (s->isGoalState())
            return this->backtrace(bfs_queue.front());
        bfs_queue.pop();
        if (bfs_queue.empty())
            return this->NOT_FOUND;
        s->updateState(bfs_queue.front());
    }
    return this->NOT_FOUND;
}

#endif //EX4_BFS_H
