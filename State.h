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
    bool operator<(const State<T>& p1) const;
    void setVisit();
    State<T>* getFather();
    T* getPoint();
    int getValue();
    void setFather(State<T>* f);
    std::string getDirection(T* s);
    double astarF = -1, astarH = 0, astarG = 0;
};

template <typename T>
State<T>::State(T *state, int val, State<T> *father) {
    this->state = state;
    this->value = val;
    this->father = father;
    this->visited = false;
    this->astarG = val;
}

/**
 * the operator compares two nodes in the graph
 * @tparam T
 * @param s
 * @return
 */
template <typename T>
bool State<T>::operator==(const State<T>& s) const{
    return *this->state == *s.state;
}
/**
 *
 * @tparam T
 * @param s
 * @return
 */
template <typename T>
bool State<T>::operator<(const State<T>& s) const{
    if (*this->value == -1 && *s.value == -1)
        return false;
    else if (*this->value == -1) {
        return true;
    } else if (*s->value == -1) {
        return false;
    }
    return *this->value > *s.value;
}
/**
 *
 * --------- setters and getters --------
 *
 */
template <typename T>
void State<T>::setVisit() {
    this->visited = true;
}

template <typename T>
State<T> * State<T>::getFather() {
    return this->father;
}

template <typename T>
T* State<T>::getPoint() {
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
std::string State<T>::getDirection(T *s) {
    if(*this->getPoint() < *s) {
        return "Left";
    } else if (*this->getPoint() > *s)
        return "Right";
    else if (*this->getPoint() << *s)
        return "Up";
    else
        return "Down";
}

#endif //EX4_STATE_H
