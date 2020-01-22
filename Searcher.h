//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H

#include "Searchable.h"
#include "Util.h"
#include <string>

template <typename T>
class Searcher {
protected:
    int nodesEvaluated = 0;
public:
    virtual std::vector<std::string>* search(Searchable<T> *s) = 0;
    virtual std::vector<std::string>* backtrace(State<T>* state) = 0;
};

#endif //EX4_SEARCHER_H
