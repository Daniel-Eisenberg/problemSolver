////
//// Created by Daniel Eisenberg on 19/01/2020.
////
//
//#include "Util.h"
//#include "State.h"
//#include <string>
//
//
//template <typename T>
//State<T>::State(T *state, int val, State<T> *father) {
//    this->state = state;
//    this->value = val;
//    this->father = father;
//    this->visited = false;
//}
//
//template <typename T>
//bool State<T>::operator==(State *s) {
//    return this->state == s->state;
//}
//template <typename T>
//void State<T>::setVisit() {
//    this->visited = true;
//}
//
//template <typename T>
//State<T> * State<T>::getFather() {
//    return this->father;
//}
//
//template <typename T>
//T* State<T>::getState() {
//    return this->state;
//}
//
//template <typename T>
//int State<T>::getValue() {
//    return this->value;
//}
//
//template <typename T>
//void State<T>::setFather(State<T> *f) {
//    this->father = f;
//}
//
//template <typename T>
//std::string State<T>::getDiraction(T *state) {
//    if(this->getState() < state) {
//        return "up";
//    } else if (this->getState() > state)
//        return "down";
//    else if (this->getState() << state)
//        return "left";
//    else
//        return "right";
//}