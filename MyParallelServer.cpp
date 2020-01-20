//
// Created by Yuval Grinberg on 12/01/2020.
//


#include <thread>
#include "MyParallelServer.h"
#include "ClientHandler.h"
#include "MyClientHandler.h"

using namespace std;

int handleClients(const int& socket, const sockaddr_in& address, ClientHandler* client_handler);

int MyParallelServer::open(int port, ClientHandler* client_handler) {
    if (socket1 == -1) {
        std::cerr << "Could not create server socket" << std::endl;
        return -1;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // bind
    if (::bind(socket1, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an ip" << std::endl;
        return -2;
    }

    //socket listen to port
    if (listen(socket1, 1) == -1) {
        std::cerr << "Error during listening" << std::endl;
        return -3;
    }

    thread clienthandle(handleClients, socket1, address, client_handler);

//        clienthandle.detach();
    clienthandle.join();
    return 0;
}



void MyParallelServer::close() {
    close_server = true;
    unique_lock<std::mutex> ul(mtx);
    cv.wait(ul, []{return !close_server;});
    ::close(socket1);
}

bool MyParallelServer::getCloseServer() {
    return close_server;
}

int handleClients(const int& socket, const sockaddr_in& address, ClientHandler* client_handler) {
    while(!MyParallelServer::getCloseServer()) {
        struct timeval tv;
        tv.tv_sec = 2;
        setsockopt(socket1, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
        //accept client
        int client_socket = accept(socket, (struct sockaddr *) &address, (socklen_t *) &address);
        if (client_socket == -1) {
            std::cerr << "Error accepting client" << std::endl;
            return -4;
        } else
            thread parallelHandle(client_handler->handleClient, client_socket);
    }
    close_server = false;
    cv.notify_all();
}