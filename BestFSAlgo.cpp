////
//// Created by Yuval Grinberg on 21/01/2020.
////
//
//#include "BestFSAlgo.h"
//#include <string>
//#include <set>
//
//using namespace std;
//
//template <typename T>
//std::vector<std::string>* BestFSAlgo<T>::search(Searchable<T> *s) {
//
//    auto v = nullptr;
//    int bestBacktrace = -1;
//    int tempBacktrace = 0;
//    set<T> closed;
//    s->setVisit(s->getState());
//    open_pq.push(s->getState());
//    while (!open_pq.empty()) {
//
//        State<T>* n = popOpenList();
//        closed.inset(n);
//        if (s->isGoalState())
//            return this->backtrace(open_pq.front());
//        for (State<T>* state: s->getAllPossibleStates()) {
//            if (state != nullptr && !(closed.count(state) > 0) && !(open_pq.count(state) > 0)) {
//                this->nodesEvaluated++;
//                s->setVisit(state);
//                state->setFather(s);
//                open_pq.push(state);
//            } else if (bestBacktrace = -1 || bestBacktrace > (tempBacktrace = this->backtrace(open_pq.front()).size())){
//                bestBacktrace = tempBacktrace;
//                if (!(open_pq.count(state) > 0))
//                    open_pq.push(state);
//                else {
//                    open_pq(state);
//                }
//            }
//        }
//        //update state
////        if (queue.size() == 1)
////            v = this->backtrace(queue.front());
////        queue.pop();
////        s->updateState(queue.front());
//    }
//    return v;
//}
//
//template <typename T>
//std::vector<std::string>* BestFSAlgo<T>::backtrace(State<T>* state) {
//    auto v = new std::vector<std::string>();
//    auto s = state;
//    while (s != nullptr) {
//        v->push_back(s->getDirection(s->getFather()->getState()));
//        s = s.getFather();
//    }
//    return v;
//}
//
//template <typename T>
//T* BestFSAlgo<T>::popOpenList() {
//    this->nodesEvaluated++;
//    return open_pq.pop();
//}
//
