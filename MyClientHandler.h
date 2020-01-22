//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_MYCLIENTHANDLER_H
#define EX4_MYCLIENTHANDLER_H

#include <ostream>
#include <sys/socket.h>
#include <iostream>
#include <zconf.h>
#include "MyClientHandler.h"
#include "md5.h"
#include "ClientHandler.h"
#include "CacheManager.h"
#include "FilesCacheManager.h"
#include "Solver.h"


class MyClientHandler : public ClientHandler {
    Solver<string, string>* solver;
    CacheManager<string, string>* cm;
public:
    MyClientHandler(Solver<string, string>* solver, CacheManager<string, string>* cm) {
        this->solver = solver;
        this->cm = cm;
    }
    virtual void handleClient(int client_socket);
    static vector<vector<int>> reconstructMatrix(string obj);
    static std::vector<string> split(string str, string delimiter);
};


#endif //EX4_MYCLIENTHANDLER_H
