//
// Created by Daniel Eisenberg on 12/01/2020.
//

#include "StringReverser.h"

string StringReverser::solve(string prob) {
    prob = reverseStr(prob);
    return prob;
}

string StringReverser::reverseStr(string& str) {
    int n = str.length();
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}