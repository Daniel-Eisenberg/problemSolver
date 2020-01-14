//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H


#include "ClientHandler.h"
#include "CacheManger.h"
#include "Solver.h"

class MyClientHandler : public ClientHandler {

    Solver solver;
    CacheManager cm;
public:
    virtual void handleClient(int socket_server);

};


#endif //EX4_MYTESTCLIENTHANDLER_H
