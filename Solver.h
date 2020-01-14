//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H
template <typename Problem, typename Solution>
class Solver{
public:
    virtual Solution solve(Problem prob) = 0;
}
#endif //EX4_SOLVER_H
