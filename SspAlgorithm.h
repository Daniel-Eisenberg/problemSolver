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

public:
    virtual ~SspAlgorithm() = default;
};

template <typename P>
std::vector<std::string>* SspAlgorithm<P>::backtrace(State<P>* state) {
    int cost = 0;
    auto v = new std::vector<std::string>();
    auto values = new std::vector<int>();

    auto s = state;
    while (s->getFather() != nullptr) {

        values->insert(values->begin(), s->getValue());
        v->insert(v->begin(),s->getDirection(s->getFather()->getState()));
        s = s->getFather();
    }
    auto itr = v->begin();
    for (int i = 0; i < values->size(); i++) {
        itr = v->begin() + 2*i + 1;
        v->insert(itr, "(" + std::to_string(values->at(i)) + ")");
    }
    v->insert(v->begin(), "Trace: ");
    std::string a = "cost: " + std::to_string(cost) + "\n";
    v->insert(v->begin(), a);
    return v;
}

#endif //EX3_SSPALGORITHM_H
