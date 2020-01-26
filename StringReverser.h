//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_STRINGREVERSER_H
#define EX4_STRINGREVERSER_H


#include <string>
#include "Solver.h"

using namespace std;

class StringReverser : public Solver<string, string> {
    string solve(string prob);
    string reverseStr(string str);
    virtual ~StringReverser() = default;
};


#endif //EX4_STRINGREVERSER_H
