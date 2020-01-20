//
// Created by Daniel Eisenberg on 12/01/2020.
//


#include "StringReverser.h"

/**
 * Implenetation of solve to reverse a string
 * @param prob
 * @return
 */
string StringReverser::solve(string prob) {
    prob = reverseStr(prob);
    return prob;
}

string StringReverser::reverseStr(string s) {
    string rev;
    for (int i = s.size() - 1; i >= 0; i--) {
        rev = rev.append(1, s[i]);
    };

    return rev;
}