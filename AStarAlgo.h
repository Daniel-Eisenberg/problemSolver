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
    std::priority_queue<State<T>*> open_pq;
public:
    virtual std::vector<std::string>* search(Searchable<T>* s);
    virtual std::vector<std::string>* backtrace(State<T>* state);
    virtual T* popOpenList();
    float heuristicCalc(int cur_x, int cur_y, int goal_x, int goal_y);
};

template <typename T>
// Flip the sign to create min heap
bool operator<(const State<T>* n1, const State<T>* n2) {
    return n1->astarF > n2->astarF;
}

template <typename T>
bool operator==(const State<T>* n1, const State<T>* n2) {
    return n1->x == n2->x && n1->y == n2->y && n1->value == n2->value;
}

template <typename T>
std::vector<std::string>* AStarAlgo<T>::search(Searchable<T> *s) {
    set<State<T>*> closed;
    s->setVisit(s->getState());
    open_pq.push(s->getState());
    while (!open_pq.empty()) {
        State<T> *q = popOpenList();

        vector<State<T>*>* nbrs = s->getAllPossibleStates();
        for (int i = 0; i < 4; ++i) {
            State<T>* nbr = nbrs[i];
            if (s->isGoalState(nbr))
                return this->backtrace(nbr);

            if (!(closed.find(nbr) > 0)) {
                double newG = q->astarG + q->getValue();
                double newH = heuristicCalc(nbr->x, nbr->y, s->matrix_size, s->matrix_size);
                double newF = newG + newH;
                if (nbr->astarF == -1 || nbr->astarF > newF) {
                    nbr->setFather(s);
                    open_pq.push(nbr);

                    nbr->astarG = newG;
                    nbr->astarH = newH;
                    nbr->astarF = newF;
                }
            }
        }

        closed.push(q);
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
float AStarAlgo<T>::heuristicCalc(int cur_x, int cur_y, int goal_x, int goal_y) {
    return std::abs(cur_x - goal_x) + std::abs(cur_y - goal_y);
}

#endif //EX3_ASTARALGO_H
