//
// Created by Daniel Eisenberg on 17/01/2020.
//

#ifndef EX4_OA_H
#define EX4_OA_H

#include "Solver.h"
#include "Searcher.h"
#include "Matrix.h"
#include "AStarAlgo.h"
#include "Util.h"

using namespace std;

template <typename Problem, typename Solution>
class OA : public Solver<Problem, Solution> {
public:
    /**
     * instantiate a searcher object and a searchable based on clients messages and return the solution for the problem.
     * @param problem
     * @return
     */
    virtual Solution solve(Problem problem) {
        vector<string> lines = split(problem, "\n");
        lines.pop_back();
        int size = lines.size();
        string goal_str = lines.at(size - 1);
        string start_str = lines.at(size - 2);
        lines.pop_back();
        lines.pop_back();
        vector<vector<int>> matrix_vec = reconstructMatrix(&lines);

        State<myPoint>* goal_state = reconstructPoint(goal_str, matrix_vec);
        State<myPoint>* start_state = reconstructPoint(start_str, matrix_vec);

        Matrix* matrix = new Matrix(&matrix_vec, start_state, goal_state);
        Searcher<myPoint>* algo = new AStarAlgo<myPoint>();
        vector<string>* result = algo->search(matrix);
        
        string result_str = "";
        for (string str : *result) {
            result_str = result_str + str + ",";
        }
        result_str = result_str.substr(0, result_str.length() - 1);


        delete algo;
        delete result;

        return result_str;
    };

    State<myPoint>* reconstructPoint(string line, vector<vector<int>> matrix_vec) {
        vector<string> line_str = split(line, ",");
        int x = stoi(line_str.at(0));
        int y = stoi(line_str.at(0));
        myPoint* po = new myPoint(x,y, matrix_vec.at(x).at(y));
        State<myPoint>* state = new State<myPoint>(po, po->value, nullptr);
        return state;
    }

    /**
     * makes a matrix object from clients messages
     * @param obj the message from the client
     * @return matrix
     */
    vector<vector<int>> reconstructMatrix(vector<string>* lines) {
        vector<vector<int>> result;
        for (string line : *lines) {
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

    /**
     * split a string by a delimeter in form of a string.
     */
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

    virtual ~OA() = default;
};


#endif //EX4_OA_H
