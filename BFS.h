//
// Created by Daniel Eisenberg on 17/01/2020.
//

#ifndef EX4_BFS_H
#define EX4_BFS_H

#include "queue"
#include "Searcher.h"
#include "Matrix.h"
template <typename T>
class BFS : public Searcher<T> {
    std::queue<T> queue;
public:
    virtual std::vector<std::string>* search(Searchable<T>* s);
    virtual std::vector<std::string>* backtrace(State<T>* state);
};


#endif //EX4_BFS_H
