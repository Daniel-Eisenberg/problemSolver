//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H


#include "Server.h"
using namespace server_side;
class MyParallelServer : public Server {
    virtual int open(int port, ClientHandler& clinethandler);
    virtual void close();
};


#endif //EX4_MYSERIALSERVER_H
