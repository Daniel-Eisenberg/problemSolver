//
// Created by Yuval Grinberg on 12/01/2020.
//


#include <thread>
#include "MyParallelServer.h"
#include "ClientHandler.h"

using namespace std;

int MyParallelServer::maxParallel = 0;
int MyParallelServer::currentParallel = 0;

int handleClients(const int& socket, const sockaddr_in& address, ClientHandler* client_handler);

int MyParallelServer::open(int port, ClientHandler* client_handler) {
    if (socket2 == -1) {
        std::cerr << "Could not create server socket" << std::endl;
        return -1;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // bind
    if (::bind(socket2, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an ip" << std::endl;
        return -2;
    }

    //socket listen to port
    if (listen(socket2, 1) == -1) {
        std::cerr << "Error during listening" << std::endl;
        return -3;
    }

    thread clienthandle(handleClients, socket2, address, client_handler);

//        clienthandle.detach();
    clienthandle.join();
    return 0;
}



void MyParallelServer::close() {
    close_server_par = true;
    unique_lock<std::mutex> ul(mtx_par);
    cv_par.wait(ul, []{return !close_server_par;});
    ::close(socket2);
}

bool MyParallelServer::getCloseServer() {
    return close_server_par;
}

int MyParallelServer::handleClients(const int& socket, const sockaddr_in& address, ClientHandler* client_handler) {
    vector<thread> threadPool;
    while(!MyParallelServer::getCloseServer()) {
        if (currentParallel >= maxParallel) {
            sleep(2000);
            continue;
        }
        struct timeval tv;
        tv.tv_sec = 2;
        setsockopt(socket2, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
        //accept client
        int client_socket = accept(socket, (struct sockaddr *) &address, (socklen_t *) &address);
        if (client_socket == -1) {
            std::cerr << "Error accepting client" << std::endl;
            return -4;
        } else {
            threadPool.push_back(thread(parallelHandleClient, client_socket, client_handler));
            currentParallel++;
        }
    }
    close_server_par = false;
    cv_par.notify_all();
    return 0;
}

void MyParallelServer::parallelHandleClient(const int& client_socket, ClientHandler* client_handler) {
    client_handler->handleClient(client_socket);
}
