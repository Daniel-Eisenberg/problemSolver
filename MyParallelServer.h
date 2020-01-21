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

static int socket2 = socket(AF_INET, SOCK_STREAM, 0);
static std::mutex mtx_par;
static bool close_server_par = false;
static std::condition_variable cv_par;

class MyParallelServer : public Server {
    static int maxParallel;
    virtual int open(int port, ClientHandler* clinethandler);
    virtual void close();
public:
    static int currentParallel;

    MyParallelServer(int maxParallelArg) {
        this->maxParallel = maxParallelArg;
    };
    static bool getCloseServer();
    int static handleClients(const int& socket, const sockaddr_in& address, ClientHandler* client_handler);
    void static parallelHandleClient(const int& client_socket, ClientHandler* client_handler);
    };


#endif //EX4_MYPARALLELSERVER_H
