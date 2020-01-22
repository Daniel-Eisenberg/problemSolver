////
//// Created by Yuval Grinberg on 21/01/2020.
////
//
//#include "DFSAlgo.h"
//#include <string>
//#include <algo_stack>
//
//using namespace std;
//
//template <typename T>
//std::vector<std::string>* DFSAlgo<T>::search(Searchable<T> *s) {
//
//    auto v = nullptr;
//    s->setVisit(s->getState());
//    algo_stack.push(s->getState());
//
//    while (!algo_stack.empty()) {
//        s->updateState(algo_stack.pop());
//        if (!s->visited(s->getState())) {
//            s->setVisit(s->getState());
//
//            for (State<T>* state: s->getAllPossibleStates()) {
//                if (state != nullptr && !s->visited(state)) {
//                    this->nodesEvaluated++;
//                    s->setVisit(state);
//                    state->setFather(s);
//                    algo_stack.push(state);
//                }
//            }
//        }
//
//        if (algo_stack.size() == 1)
//            return this->backtrace(s);
//    }
//    return v;
//}
//
//template <typename T>
//std::vector<std::string>* DFSAlgo<T>::backtrace(State<T>* state) {
//    auto v = new std::vector<std::string>();
//    auto s = state;
//    while (s != nullptr) {
//        v->push_back(s->getDirection(s->getFather()->getState()));
//        s = s.getFather();
//    }
//    return v;
//}