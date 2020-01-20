//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H


#include "Server.h"
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <zconf.h>
#include "MySerialServer.h"
#include "ClientHandler.h"
#include "MyClientHandler.h"
#include <vector>
#include <thread>
#include <mutex>
using namespace server_side;
static int socket1 = socket(AF_INET, SOCK_STREAM, 0);
static std::mutex mtx;
static bool close_server = false;
static std::condition_variable cv;
class MySerialServer : public Server {
    virtual int open(int port, ClientHandler* clinethandler);
    virtual void close();

public:
    static bool getCloseServer();
};


#endif //EX4_MYSERIALSERVER_H
