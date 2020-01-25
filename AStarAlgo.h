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
    s->getState()->astarF = heuristicCalc(s->getState()->getPoint()->x, s->getState()->getPoint()->y,
                                          s->getGoalState()->getPoint()->x,
                                          s->getGoalState()->getPoint()->y);
    open_pq.insert(s->getState());
    while (!open_pq.empty()) {
        State<T>* q = *(min_element(open_pq.begin(), open_pq.end(),
                                    [] (State<T> *left, State<T> *right) -> bool {
                                        return left->astarF < right->astarF; }));
        open_pq.erase(q);
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

            double tentativeG = q->astarG + nbr->getValue();
            if (nbr->astarF == -1 || nbr->astarG > tentativeG) {
                nbr->setFather(q);

                nbr->astarG = tentativeG;
                nbr->astarH = heuristicCalc(nbr->getPoint()->x, nbr->getPoint()->y, q->getPoint()->x, q->getPoint()->y);
                nbr->astarF = nbr->astarG + nbr->astarH;

                if (!(open_pq.count(nbr) > 0))
                    open_pq.insert(nbr);
            }
        }
    }
    return this->NOT_FOUND;
}

// Manhatan calc
template <typename T>
float AStarAlgo<T>::heuristicCalc(int cur_x, int cur_y, int goal_x, int goal_y) {
    return std::abs(cur_x - goal_x) + std::abs(cur_y - goal_y);
}

#endif //EX3_ASTARALGO_H
