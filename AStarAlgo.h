//
// Created by Yuval Grinberg on 21/01/2020.
//

#ifndef EX3_ASTARALGO_H
#define EX3_ASTARALGO_H

#include "queue"
#include "Searcher.h"
#include "SspAlgorithm.h"
#include <set>
#include <iostream>

using namespace std;

template <typename T>
class AStarAlgo : public SspAlgorithm<T>  {
    set<State<T>*> open_pq;
public:
    virtual std::vector<std::string>* search(Searchable<T>* s);
    float heuristicCalc(int cur_x, int cur_y, int goal_x, int goal_y);
};


template <typename T>
std::vector<std::string>* AStarAlgo<T>::search(Searchable<T> *s) {
    set<State<T>*> closed;
    s->setVisit(s->getState());
    open_pq.insert(s->getState());
    while (!open_pq.empty()) {
        State<T> *q = *open_pq.begin();
        open_pq.erase(open_pq.begin());
        closed.insert(q);
        s->updateState(q);
        s->setVisit(q);


        vector<State<T>*>* neighbors = s->getAllPossibleStates();
        for (int i = 0; i < 4; ++i) {
            State<T>* nbr = neighbors->at(i);
            if (nbr == nullptr || nbr->getValue() == -1)
                continue;

            if (s->isGoalState(*nbr)) {
                nbr->setFather(q);
                return this->backtrace(nbr);
            }

            if (!(closed.count(nbr) > 0) && !(open_pq.count(nbr) > 0)) {
                double newG = q->astarG + q->getValue();
                double newH = heuristicCalc(nbr->getState()->x, nbr->getState()->y, s->getGoalState()->getState()->x, s->getGoalState()->getState()->y);
                double newF = newG + newH;
                if (nbr->astarF == -1 || nbr->astarF > newF) {
                    nbr->setFather(q);

                    open_pq.insert(nbr);

                    nbr->astarG = newG;
                    nbr->astarH = newH;
                    nbr->astarF = newF;
                }
            }
        }

    }
}

// Manhatan calc
template <typename T>
float AStarAlgo<T>::heuristicCalc(int cur_x, int cur_y, int goal_x, int goal_y) {
    return std::abs(cur_x - goal_x) + std::abs(cur_y - goal_y);
}

#endif //EX3_ASTARALGO_H
