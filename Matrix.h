//
// Created by Daniel Eisenberg on 17/01/2020.
//

#ifndef EX4_MATRIX_H
#define EX4_MATRIX_H
#include <vector>
#include <MacTypes.h>
#include <map>
#include "Util.h"
#include "Searchable.h"
#include <string>
#include <memory>
#include "State.h"

using namespace std;
class Matrix : public Searchable<myPoint>{

    std::vector<std::vector<int>>* matrix;
    std::vector<State<myPoint>*> *all_possible_states;
    std::map<std::pair<int, int>, State<myPoint>*> *all_saved_states;
    State<myPoint>* goalState;

public:
    Matrix(std::vector<std::vector<int>> *matrix);
    virtual State<myPoint>* getGoalState();
    bool isGoalState();
    bool isGoalState(State<myPoint> dest);
    void setAllPossibleStates();
    std::vector<State<myPoint>*>* getAllPossibleStates();
    virtual void updateState(State<myPoint> *next);
    virtual void setVisit(State<myPoint> *s);
    virtual State<myPoint>* getState();
    void updateDirection(std::pair<int, int> point, std::string _case);
    bool visited(State<myPoint>* p);
    void setInitialState();
    ~Matrix(){};
};

Matrix::Matrix(std::vector<std::vector<int>> *matrix) : Searchable(), matrix(matrix) {
    auto *p = new myPoint(0,0, matrix->at(0).at(0));
    this->state = new State<myPoint>(p, p->value, nullptr);
    this->all_saved_states = new map<std::pair<int,int>, State<myPoint>*>();
    all_possible_states = nullptr;
    setInitialState();

    int size = this->matrix->size();
    myPoint* goal_point = new myPoint(size - 1, this->matrix[0].size() - 1, this->matrix->at(size - 1).at(size - 1));
    State<myPoint>* goal_state = new State<myPoint>(goal_point, goal_point->value, nullptr);
    this->goalState = goal_state;
};


bool Matrix::isGoalState() {
    return (*this->state == *this->goalState);
}

bool Matrix::isGoalState(State<myPoint> dest) {
    return (dest == *this->goalState);
}

State<myPoint>* Matrix::getGoalState() {
    return this->goalState;
}

void Matrix::setInitialState() {
    myPoint *up = nullptr, *left = nullptr, *down = nullptr, *right = nullptr;
    //set for the first time
    this->all_possible_states = new std::vector<State<myPoint> *>();
    this->all_possible_states->push_back(nullptr);
    //matrix has more then one line
    if (this->matrix->size() > 1) {
        down = new myPoint(1, 0, this->matrix->at(1).at(0));
        auto s2 = new State<myPoint>(down, down->value, nullptr);
        this->all_possible_states->push_back(s2);
        std::pair<int, int> pair_s2 (s2->getState()->x, s2->getState()->y);
        std::pair<std::pair<int, int>, State<myPoint>*> pair2(pair_s2, s2);
        this->all_saved_states->insert(pair2);

    }
    else {
        this->all_possible_states->push_back(nullptr);
    }
    //matrix has more then one column
    if (this->matrix->at(0).size() > 1) {
        right = new myPoint(0, 1, this->matrix->at(0).at(1));
        auto s1 = new State<myPoint>(right, right->value, nullptr);
        this->all_possible_states->push_back(s1);
        std::pair<int, int> pair_s1 (s1->getState()->x, s1->getState()->y);
        std::pair<std::pair<int, int>, State<myPoint>*> pair1(pair_s1, s1);
        this->all_saved_states->insert(pair1);

    } else {
        this->all_possible_states->push_back(nullptr);
    }


    this->all_possible_states->push_back(nullptr);
    std::pair<int, int> pair_s3 (0, 0);
    std::pair<std::pair<int, int>, State<myPoint>*> pair3(pair_s3, this->state);
    this->all_saved_states->insert(pair3);

}

void Matrix::updateDirection(std::pair<int, int> point, std::string _case) {

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
        auto p = new myPoint(point.first, point.second,
                             this->matrix->at(point.first).at(point.second));
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
    bool has_down = this->state->getState()->x + 1 <= this->matrix->size() - 1;
    bool has_left = this->state->getState()->y - 1 >= 0;
    bool has_right = this->state->getState()->y + 1 <= this->matrix->at(0).size() - 1;
    //check up
    std::pair<int, int> point;
    if (has_up) {
        updateDirection(point, "up");
    } else {
        this->all_possible_states->at(0) = nullptr;
    }
    //check down
    if (has_down) {
        updateDirection(point, "down");
    } else {
        this->all_possible_states->at(1) = nullptr;
    }
    //check right
    if (has_right) {
        updateDirection(point, "right");
    } else {
        this->all_possible_states->at(2) = nullptr;
    }
    //check left
    if (has_left) {
        updateDirection(point, "left");
    } else {
        this->all_possible_states->at(3) = nullptr;
    }

}

std::vector<State<myPoint>*>* Matrix::getAllPossibleStates() {
    return this->all_possible_states;
}

bool Matrix::visited(State<myPoint> *p) {
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

#endif //EX4_MATRIX_H
