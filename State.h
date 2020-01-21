//
// Created by Daniel Eisenberg on 19/01/2020.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H


#include <string>

template <typename T>
class State {
    T* state;
    int value;
    bool visited;
    State<T>* father;
public:
    State(T* state, int val, State<T>* father);
    bool operator==(State* s);
    void setVisit();
    State<T>* getFather();
    T* getState();
    int getValue();
    void setFather(State<T>* f);
    std::string getDiraction(T* state);

};


#endif //EX4_STATE_H
