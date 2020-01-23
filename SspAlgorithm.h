//
// Created by Yuval Grinberg on 22/01/2020.
//

#ifndef EX3_SSPALGORITHM_H
#define EX3_SSPALGORITHM_H


#include "Searcher.h"
/**
 * class to hold a common function between all the objects that are implementing Searcher interface.
 */
template <typename P>
class SspAlgorithm : public Searcher<P>{
protected:
    std::vector<std::string>* backtrace(State<P>* state);
};

template <typename P>
std::vector<std::string>* SspAlgorithm<P>::backtrace(State<P>* state) {
    auto v = new std::vector<std::string>();
    auto s = state;
    while (s->getFather() != nullptr) {
        v->insert(v->begin(),s->getDirection(s->getFather()->getState()));
        s = s->getFather();
    }
    return v;
}

#endif //EX3_SSPALGORITHM_H
