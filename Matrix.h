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
    Matrix(std::vector<std::vector<int>> *matrix, State<myPoint>* start,State<myPoint>* _end);
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
    ~Matrix();
};

Matrix::Matrix(std::vector<std::vector<int>> *matrix, State<myPoint>* start,State<myPoint>* _end) : Searchable(), matrix(matrix) {
    this->state = start;
    this->goalState = _end;
    this->all_saved_states = new map<std::pair<int,int>, State<myPoint>*>();
    std::pair<int, int> point = make_pair(start->getState()->x, start->getState()->x);
    auto pr = make_pair(point, start);
    this->all_saved_states->insert(pr);
    this->all_possible_states = new std::vector<State<myPoint> *>();
    this->all_possible_states->push_back(nullptr);
    this->all_possible_states->push_back(nullptr);
    this->all_possible_states->push_back(nullptr);
    this->all_possible_states->push_back(nullptr);
    setAllPossibleStates();
};

/**
 * check wether we are in the last node of th graph
 * @return true if we are at the last node of the graph false otherwise
 */
bool Matrix::isGoalState() {
    return (*this->state == *this->goalState);
}
/**
 * check wether a node is the last node of th graph
 * @param dest
 * @return true if dest is the last node of the graph false otherwise
 */
bool Matrix::isGoalState(State<myPoint> dest) {
    return (dest == *this->goalState);
}
/**
 * @return the last node of the graph
 */
State<myPoint>* Matrix::getGoalState() {
    return this->goalState;
}

/**
 * set the given neighbors
 * @param point pair to work with, just for conviniency
 * @param _case the neighbors to update
 */
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
 * update the neighbors of a node in the graph
 */
void Matrix::setAllPossibleStates() {

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
/**
 * @return all neighbors to the current node
 */
std::vector<State<myPoint>*>* Matrix::getAllPossibleStates() {
    return this->all_possible_states;
}

/**
 * check if a given node has been visited
 * @param p the node
 * @return true if it has been visited false otherwise
 */
bool Matrix::visited(State<myPoint> *p) {
    return p->visited;
}

/**
 * change the current node to a given node
 * @param next the given node
 */
void Matrix::updateState(State<myPoint> *next) {

    this->state = next;
    setAllPossibleStates();
}
/**
 * update that a given node has been visited and update the counter thats incharge of counting the number of nodes visited by the algorithm
 * @param s
 */
void Matrix::setVisit(State<myPoint> *s) {
    this->nodesEvaluated++;
    s->setVisit();
}
/**
 * @return the current node
 */
State<myPoint>* Matrix::getState() {
    return this->state;
}

Matrix::~Matrix() {
    delete matrix;
    for (State<myPoint>* a : *all_possible_states) {
        delete a;
    }
    delete all_possible_states;
    for (auto b: *all_saved_states) {
        delete b.second;
    }
    delete all_saved_states;
    delete goalState;
}
#endif //EX4_MATRIX_H
