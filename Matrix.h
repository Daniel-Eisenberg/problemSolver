//
// Created by Daniel Eisenberg on 17/01/2020.
//

#ifndef EX4_MATRIX_H
#define EX4_MATRIX_H


#include "Searchable.h"
#include "State.h"
#include <vector>
#include <MacTypes.h>
#include <unordered_map>

struct myPoint {
    int x;
    int y;
    int value;
    bool visited;

    myPoint(int x, int y, int value) {
        this->x = x;
        this->y = y;
        this->value =value;
        this->visited = false;
    }

    bool operator== (const myPoint& p) {
        return (this->x == p.x && this->y == p.y);
    }

    //return true if the point is above "this" point
    bool operator< (const myPoint& p) {
        return (this-> x == p.x && this-> y < p.y);
    }

    //return true if the point is on the right to  "this" point
    bool operator<< (const myPoint& p) {
        return (this->y == p.y && this->x < p.x);
    }

    //return true if the point is on the below "this" point
    bool operator> (const myPoint& p) {
        return (this->x == p.x && this-> y > p.y);
    }

    //return true if the point is on the left to "this" point
    bool operator>> (const myPoint& p) {
        return (this->y == p.y && this->x > p.x);
    }
};

class Matrix : public Searchable<myPoint>{


    std::vector<std::vector<int>>* matrix;
    std::vector<State<myPoint>*> *all_possible_states;
    std::unordered_map<std::pair<int, int>, State<myPoint>*> *all_saved_states;


public:
    Matrix(std::vector<std::vector<int>>* matrix);
    bool isGoalState();
    void setAllPossibleStates();
    std::vector<State<myPoint>*>* getAllPossibleStates();
    virtual void updateState(State<myPoint> *next);
    virtual void setFatherstate();
    virtual void setVisit(State<myPoint> *s);
    virtual State<myPoint>* getState();
    bool visited(myPoint* p);
    void setInitialState();
    ~Matrix();
};


#endif //EX4_MATRIX_H
