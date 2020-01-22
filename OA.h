//
// Created by Daniel Eisenberg on 17/01/2020.
//

#ifndef EX4_OA_H
#define EX4_OA_H

#include "Solver.h"
#include "Searcher.h"
#include "Matrix.h"
#include "BFS.h"
#include "Util.h"

using namespace std;

template <typename Problem, typename Solution>
class OA : public Solver<Problem, Solution> {
public:
    virtual Solution solve(Problem problem) {
        vector<vector<int>> matrix_vec = reconstructMatrix(problem);
        Matrix* matrix = new Matrix(&matrix_vec);
        Searcher<myPoint>* algo = new BFS<myPoint>();
        vector<string>* result = algo->search(matrix);
        string result_str = "";
        for (string str : *result) {
            result_str = result_str + str + ",";
        }
        result_str = result_str.substr(0, result_str.length() - 1);
        return result_str;
    };

    vector<vector<int>> reconstructMatrix(string obj) {
        vector<vector<int>> result;
        vector<string> lines = split(obj, "\n");
        for (string line : lines) {
            if (line != "") {
                vector<string> line_str = split(line, ",");
                vector<int> line_int;
                for (string piece : line_str) {
                    int num = stoi(piece);
                    line_int.push_back(num);
                }
                result.push_back(line_int);
            }

        }
        return result;
    };

    vector<string> split(string str, string delimiter){
        vector<string> arr;
        size_t pos = 0;
        string token;
        while ((pos = str.find(delimiter)) != string::npos) {
            token = str.substr(0, pos);
            if (token != "")
                arr.push_back(token);
            str.erase(0, pos + delimiter.length());
        }
        arr.push_back(str);
        return arr;
    };
};


#endif //EX4_OA_H
