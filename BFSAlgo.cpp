////
//// Created by Daniel Eisenberg on 17/01/2020.
////
//
//#include <string>
//#include "BFS.h"
//
//
//template <typename T>
//std::vector<std::string>* BFS<T>::search(Searchable<T> *s) {
//
//    auto v = nullptr;
//    s->setVisit(s->getState());
//    bfs_queue.push(s->getState());
//    while (!bfs_queue.empty()) {
//
//        for (State<T>* state: s->getAllPossibleStates()) {
//            if (state != nullptr && !s->visited(state)) {
//                s->setVisit(state);
//                state->setFather(s);
//                bfs_queue.push(state);
//            }
//        }
//        //update state
//        if (bfs_queue.size() == 1)
//            v = this->backtrace(bfs_queue.front());
//        bfs_queue.pop();
//        s->updateState(bfs_queue.front());
//    }
//    return v;
//}
//
//template <typename T>
//std::vector<std::string>* BFS<T>::backtrace(State<T>* state) {
//    auto v = new std::vector<std::string>();
//    auto s = state;
//    while (s != nullptr) {
//        v->push_back(s->getDirection(s->getFather()->getState()));
//        s = s.getFather();
//    }
//    return v;
//}
//
