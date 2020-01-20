//
// Created by Daniel Eisenberg on 17/01/2020.
//

#ifndef EX4_OA_H
#define EX4_OA_H

#include "Solver.h"
#include "Searcher.h"
template <typename Problem, typename Solution>
class OA : public Solver<Problem, Solution> {
    virtual Solution solve(Problem prob);
};


#endif //EX4_OA_H
