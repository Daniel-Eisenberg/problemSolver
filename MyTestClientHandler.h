//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H


#include "ClientHandler.h"
#include "CacheManger.h"
#include "Solver.h"

template <typename P,typename S>

class MyTestClientHandler : public ClientHandler {
    Solver<P, S>* solver;
    CacheManager* cm;
public:
    virtual void handleClient(std::istream InputStream, std::ostream OutputStream);

};


#endif //EX4_MYTESTCLIENTHANDLER_H
