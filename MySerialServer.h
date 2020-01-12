//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H


#include "Server.h"
using namespace server_side;
class MySerialServer : public Server {
    virtual int open(int port, ClientHandler& clinethandler);
    virtual int close();
};


#endif //EX4_MYSERIALSERVER_H
