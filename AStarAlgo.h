//
// Created by Yuval Grinberg on 21/01/2020.
//

#ifndef EX3_ASTARALGO_H
#define EX3_ASTARALGO_H

#include "queue"
#include "Searcher.h"
#include "Matrix.h"
#include <set>

template <typename T>
class AStarAlgo : public Searcher<T>  {
    std::priority_queue<T> open_pq;
public:
    virtual std::vector<std::string>* search(Searchable<T>* s);
    virtual std::vector<std::string>* backtrace(State<T>* state);
    virtual T* popOpenList();
    float l1_norm(int i0, int j0, int i1, int j1);
};


template <typename T>
std::vector<std::string>* AStarAlgo<T>::search(Searchable<T> *s) {
    const float INF = std::numeric_limits<float>::infinity();
    int w = s->matrix_size;
    auto v = nullptr;
    volatile int bestBacktrace = -1;
    int* nbrs = new int[8];
    float* costs = new float[w * w];
    for (int i = 0; i < w * w; ++i)
        costs[i] = INF;
    costs[0] = 0.;

    set<T> closed;
    s->setVisit(s->getState());
    open_pq.push(s->getState());
    while (!open_pq.empty()) {

        State<T>* n = popOpenList();
        closed.inset(n);
        if (s->isGoalState())
            return this->backtrace(open_pq.front());

        int cur_x = n->getState().x;
        int row = cur_x / w;
        int col = cur_x % w;
        // check bounds and find up to eight neighbors: top to bottom, left to right
        nbrs[0] = (row > 0) ? cur_x - w : -1;
        nbrs[1] = (col > 0) ? cur_x - 1 : -1;
        nbrs[2] = (col + 1 < w) ? cur_x + 1 : -1;
        nbrs[3] = (row + 1 < w) ? cur_x + w : -1;


        int goal = 10;
        auto pos_states = s->getAllPossibleStates();
        float heuristic_cost;
        for (int i = 0; i < 4; ++i) {
            if (nbrs[i] >= 0) {
                State<T>* state = pos_states.at(cur_x);
                // the sum of the cost so far and the cost of this move
                float new_cost = state->getPriority() + costs[nbrs[i]];
                if (new_cost < costs[nbrs[i]]) {
                    // estimate the cost to the goal based on legal moves
                    heuristic_cost = l1_norm(nbrs[i] / w, nbrs[i] % w, goal / w, goal % w);

                    // paths with lower expected cost are explored first
                    float priority = new_cost + heuristic_cost;
                    open_pq.push(nbrs[i]);

                    costs[nbrs[i]] = new_cost;
                    state->setFather(s);
                }
            }
        }
//
//        for (State<T>* state: s->getAllPossibleStates()) {
//            if (state != nullptr && !(closed.count(state) > 0) && !(open_pq.count(state) > 0)) {
//                this->nodesEvaluated++;
//                s->setVisit(state);
//                state->setFather(s);
//                open_pq.push(state);
//            } else if (bestBacktrace = -1 || bestBacktrace > this->backtrace(open_pq.front()).size()){
//                bestBacktrace = this->backtrace(open_pq.front()).size();
//                if (!(open_pq.count(state) > 0))
//                    open_pq.push(state);
//                else {
//                    adujstPriority(state);
//                }
//            }
//        }
    }
}

template <typename T>
std::vector<std::string>* AStarAlgo<T>::backtrace(State<T>* state) {
    auto v = new std::vector<std::string>();
    auto s = state;
    while (s != nullptr) {
        v->push_back(s->getDirection(s->getFather()->getState()));
        s = s.getFather();
    }
    return v;
}

template <typename T>
T* AStarAlgo<T>::popOpenList() {
    this->nodesEvaluated++;
    return open_pq.pop();
}

template <typename T>
float AStarAlgo<T>::l1_norm(int i0, int j0, int i1, int j1) {
    return std::abs(i0 - i1) + std::abs(j0 - j1);
}

#endif //EX3_ASTARALGO_H
