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
    set<State<T>*> open_nodes;
public:
    virtual std::vector<std::string>* search(Searchable<T>* s);
    float heuristicCalc(int cur_x, int cur_y, int goal_x, int goal_y);
};

/**
 * A*Star algorithm
 * @tparam T node in the graph
 * @param s object that represents the graph
 * @return the way to go from the first node to destination
 */
template <typename T>
std::vector<std::string>* AStarAlgo<T>::search(Searchable<T> *s) {
    set<State<T>*> closed;
    s->setVisit(s->getState());
    s->getState()->astarF = heuristicCalc(s->getState()->getPoint()->x, s->getState()->getPoint()->y,
                                          s->getGoalState()->getPoint()->x,
                                          s->getGoalState()->getPoint()->y);
    open_nodes.insert(s->getState());
    while (!open_nodes.empty()) {
        // Get the node with minimal F value from the open set
        State<T>* q = *(min_element(open_nodes.begin(), open_nodes.end(),
                                    [] (State<T> *left, State<T> *right) -> bool {
                                        return left->astarF < right->astarF; }));
        open_nodes.erase(q);
        s->updateState(q);
        s->setVisit(q);

        //Iterate neighbors
        vector<State<T>*>* neighbors = s->getAllPossibleStates();
        for (int i = 0; i < 4; ++i) {
            State<T>* nbr = neighbors->at(i);
            // Skip infinity of not possible nodes
            if (nbr == nullptr || nbr->getValue() == -1)
                continue;

            // If goal state was found return backtrace
            if (s->isGoalState(*nbr)) {
                nbr->setFather(q);
                return this->backtrace(nbr);
            }

            // If tentantive calc is smaller than neighbors G value
            // or the node doesn't have a F value go to it
            double tentativeG = q->astarG + nbr->getValue();
            if (nbr->astarF == -1 || nbr->astarG > tentativeG) {
                nbr->setFather(q);

                nbr->astarG = tentativeG;
                nbr->astarH = heuristicCalc(nbr->getPoint()->x, nbr->getPoint()->y, q->getPoint()->x, q->getPoint()->y);
                nbr->astarF = nbr->astarG + nbr->astarH;

                if (!(open_nodes.count(nbr) > 0))
                    open_nodes.insert(nbr);
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
