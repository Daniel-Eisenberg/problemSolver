//
// Created by Daniel Eisenberg on 17/01/2020.
//

#include "Matrix.h"
#include <string>

Matrix::Matrix(std::vector<std::vector<int>> *matrix) : Searchable(), matrix(matrix) {
    auto *p = new myPoint(0,0, matrix->at(0).at(0));
    this->state = new State<myPoint>(p, p->value, nullptr);
    this->all_saved_states = new std::unordered_map<std::pair<int,int>, State<myPoint>>();
    all_possible_states = nullptr;
    setInitialState();
};

bool Matrix::isGoalState() {
    auto p = myPoint(this->matrix->size(), this->matrix[0].size(), this->matrix->at(this->matrix->size()).at(this->matrix->size()));
    State<myPoint> s = State<myPoint>(&p, p.value, nullptr);
   return (this->state == &s);
}

void Matrix::setInitialState() {
    myPoint *up = nullptr, *left = nullptr, *down = nullptr, *right = nullptr;
    //set for the first time
    down = new myPoint(1, 0, this->matrix->at(1).at(0));
    right = new myPoint(0, 1, this->matrix->at(0).at(1));
    this->all_possible_states = new std::vector<State<myPoint> *>();
    auto s1 = new State<myPoint>(right, right->value, this->state);
    auto s2 = new State<myPoint>(down, down->value, this->state);
    this->all_possible_states->push_back(nullptr);
    this->all_possible_states->push_back(s2);
    this->all_possible_states->push_back(nullptr);
    this->all_possible_states->push_back(s1);
    //////////
    ////////// insert to all saved states

    std::pair<int, int> _s1 (s1->getState()->x, s1->getState()->x);
    std::pair<int, int> _s2 (s2->getState()->x, s2->getState()->x);
    this->all_saved_states[_s1] = s1;

}
/**
 * index 0 - up
 * index 1 - down
 * index 2 - left
 * index 3 - right
 */
void Matrix::setAllPossibleStates() {

    myPoint *up = nullptr, *left = nullptr, *down = nullptr, *right = nullptr;
    bool has_up = this->state->getState()->y - 1 >= 0;
    bool has_down = this->state->getState()->y + 1 <= this->matrix->size();
    bool has_left = this->state->getState()->x - 1 >= 0;
    bool has_right = this->state->getState()->x + 1 <= this->matrix->size();
    //check up
    if (has_up) {

    } else {
        this->all_possible_states->at(0) = nullptr;
    }
    //check down
    if (has_down) {

    } else {
        this->all_possible_states->at(0) = nullptr;
    }
    //check right
    if (has_right) {

    } else {
        this->all_possible_states->at(0) = nullptr;
    }
    //check left
    if (has_left) {

    } else {
        this->all_possible_states->at(0) = nullptr;
    }

}

std::vector<State<myPoint>*>* Matrix::getAllPossibleStates() {
    return this->all_possible_states;
}

bool Matrix::visited(myPoint *p) {
    return p->visited;
}

/**
 * -----------------implemantion---------------------
 *
 *      1. update the new "all posible states" vector"
 *      2. make sure deleting
 *
 *
 * --------------------------------------------------
 */
void Matrix::updateState(State<myPoint> *next) {

    this->state = next;
    setAllPossibleStates();
}



void Matrix::setVisit(State<myPoint> *s) {
    s->setVisit();
}

State<myPoint>* Matrix::getState() {
    return this->state;
}

