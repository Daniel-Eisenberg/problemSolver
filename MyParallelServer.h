//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_MYPARALLELSERVER_H
#define EX4_MYPARALLELSERVER_H

#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <zconf.h>
#include <vector>
#include "Server.h"

using namespace server_side;
static int socket1 = socket(AF_INET, SOCK_STREAM, 0);
static std::mutex mtx;
static bool close_server = false;
static std::condition_variable cv;
class MyParallelServer : public Server {
    std::vector<int>* sockets;
    virtual int open(int port, ClientHandler* clinethandler);
    virtual void close();
public:
    static bool getCloseServer();
};


#endif //EX4_MYPARALLELSERVER_H
