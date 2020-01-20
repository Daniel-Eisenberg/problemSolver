//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H

#include <ostream>
#include <sys/socket.h>
#include <iostream>
#include <zconf.h>
#include "md5.h"
#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"


class MyTestClientHandler : public ClientHandler {
    Solver<string, string>* solver;
    CacheManager<string, string>* cm;
public:
    MyTestClientHandler(Solver<string,string>* solver, CacheManager<string,string>* cm) {
        this->solver = solver;
        this->cm = cm;
    }
    virtual void handleClient(int client_socket);
};


#endif //EX4_MYTESTCLIENTHANDLER_H
