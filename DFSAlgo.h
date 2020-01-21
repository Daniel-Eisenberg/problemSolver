//
// Created by Yuval Grinberg on 21/01/2020.
//

#ifndef EX3_DFSALGO_H
#define EX3_DFSALGO_H


#include <stack>
#include "queue"
#include "Searcher.h"
#include "Matrix.h"

template <typename T>
class DFSAlgo {
    std::stack<T> stack;
public:
    virtual std::vector<std::string>* search(Searchable<T>* s);
    virtual std::vector<std::string>* backtrace(State<T>* state);
};


#endif //EX3_DFSALGO_H
