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
    auto s1 = new State<myPoint>(right, right->value, nullptr);
    auto s2 = new State<myPoint>(down, down->value, nullptr);
    this->all_possible_states->push_back(nullptr);
    this->all_possible_states->push_back(s2);
    this->all_possible_states->push_back(nullptr);
    this->all_possible_states->push_back(s1);
    std::pair<int, int> pair_s1 (s1->getState()->x, s1->getState()->x);
    std::pair<int, int> pair_s2 (s2->getState()->x, s2->getState()->x);
    std::pair<std::pair<int, int>, State<myPoint>*> pair1(pair_s1, s1);
    std::pair<std::pair<int, int>, State<myPoint>*> pair2(pair_s2, s2);
    this->all_saved_states->insert(pair1);
    this->all_saved_states->insert(pair2);

}

void Matrix::updatedirection(std::pair<int, int> point, std::string _case) {

    //set point
    int location = 0;
    if (_case == "up")
        point = std::make_pair(this->state->getState()->x - 1, this->state->getState()->y);
    else if (_case == "down") {
        point = std::make_pair(this->state->getState()->x + 1, this->state->getState()->y);
        location = 1;
    }
    else if (_case == "right") {
        point = std::make_pair(this->state->getState()->x, this->state->getState()->y + 1);
        location = 2;
    }
    else {
        point = std::make_pair(this->state->getState()->x, this->state->getState()->y - 1);
        location = 3;
    }


    auto iter = this->all_saved_states->find(point);
    if (iter != this->all_saved_states->end())
        this->all_possible_states->at(location) = iter->second;
    else {
        auto p = new myPoint(this->state->getState()->x - 1, this->state->getState()->y,
                             this->matrix->at(this->state->getState()->x - 1).at(this->state->getState()->y));
        auto up_state = new State<myPoint>(p, p->value, nullptr);
        this->all_possible_states->at(location) = up_state;
        auto pr = std::make_pair(point, up_state);
        this->all_saved_states->insert(pr);
    }
}
/**
 * index 0 - up
 * index 1 - down
 * index 2 - right
 * index 3 - left
 */
void Matrix::setAllPossibleStates() {

    //myPoint *up = nullptr, *left = nullptr, *down = nullptr, *right = nullptr;
    bool has_up = this->state->getState()->x - 1 >= 0;
    bool has_down = this->state->getState()->x + 1 <= this->matrix->size();
    bool has_left = this->state->getState()->y - 1 >= 0;
    bool has_right = this->state->getState()->y + 1 <= this->matrix->size();
    //check up
    std::pair<int, int> point;
    if (has_up) {
        updatedirection(point, "up");
    } else {
        this->all_possible_states->at(0) = nullptr;
    }
    //check down
    if (has_down) {
        updatedirection(point, "down");
    } else {
        this->all_possible_states->at(1) = nullptr;
    }
    //check right
    if (has_right) {
        updatedirection(point, "right");
    } else {
        this->all_possible_states->at(2) = nullptr;
    }
    //check left
    if (has_left) {
        updatedirection(point, "left");
    } else {
        this->all_possible_states->at(3) = nullptr;
    }

}

std::vector<State<myPoint>*>* Matrix::getAllPossibleStates() {
    return this->all_possible_states;
}

bool Matrix::visited(myPoint *p) {
    return p->visited;
}


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
