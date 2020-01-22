//
// Created by Daniel Eisenberg on 19/01/2020.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H


#include <string>
#include "Util.h"

template <typename T>
class State {
    T* state;
    int value;
    State<T>* father;
public:
    bool visited;
    State(T* state, int val, State<T>* father);
    bool operator==(const State<T>& s) const;
    bool operator<(const State<T>& s) const;
    void setVisit();
    State<T>* getFather();
    T* getState();
    int getValue();
    void setFather(State<T>* f);
    std::string getDirection(T* state);
    double astarF = -1,astarH,astarG;
};


template <typename T>
State<T>::State(T *state, int val, State<T> *father) {
    this->state = state;
    this->value = val;
    this->father = father;
    this->visited = false;
}

template <typename T>
bool State<T>::operator==(const State<T>& s) const{
    return *this->state == *s.state;
}

template <typename T>
// Flip the sign to create min heap
bool State<T>::operator<(const State<T>& s) const {
    return *this->state >= *s.state;
}

template <typename T>
void State<T>::setVisit() {
    this->visited = true;
}

template <typename T>
State<T> * State<T>::getFather() {
    return this->father;
}

template <typename T>
T* State<T>::getState() {
    return this->state;
}

template <typename T>
int State<T>::getValue() {
    return this->value;
}

template <typename T>
void State<T>::setFather(State<T> *f) {
    this->father = f;
}

template <typename T>
std::string State<T>::getDirection(T *state) {
    if(*this->getState() < *state) {
        return "left";
    } else if (*this->getState() > *state)
        return "right";
    else if (*this->getState() << *state)
        return "up";
    else
        return "down";
}

#endif //EX4_STATE_H
