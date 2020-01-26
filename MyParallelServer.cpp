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

/**
 * Open a connection init client handling
 * @param port
 * @param client_handler
 * @return
 */
int MyParallelServer::open(int port, ClientHandler* client_handler) {
    if (server_socket == -1) {
        std::cerr << "Could not create server socket" << std::endl;
        return -1;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // bind
    if (::bind(server_socket, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an ip" << std::endl;
        return -2;
    }

    //socket listen to port
    if (listen(server_socket, 1) == -1) {
        std::cerr << "Error during listening" << std::endl;
        return -3;
    }

    thread clienthandle(handleClients, server_socket, address, client_handler, this);
    clienthandle.join();
    return 0;
}


/**
 * Handle multiple clients on the maximum of maxParallel member variable
 * @param socket
 * @param address
 * @param client_handler
 * @return
 */
int MyParallelServer::handleClients(const int& socket, const sockaddr_in& address, ClientHandler* client_handler, Server* server) {
    vector<thread> threadPool;
    while(true) {
        // If we are at maximum capacity of clients,
        // Wait for the first client to finish to open new space for another client
        if (currentParallel > maxParallel) {
            auto t = threadPool.begin();
            t->join();
            threadPool.erase(t);
        }
        // Set a timeout of 2 mins of no connection to server
        struct timeval tv = {120, 0};
        setsockopt(server_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
        //accept client
        int client_socket = accept(server_socket, (struct sockaddr *) &address, (socklen_t *) &address);
        if (client_socket == -1) {
            std::cerr << "Error accepting client" << std::endl;
            break;
        } else {
            threadPool.push_back(thread(parallelHandleClient, client_socket, client_handler));
            currentParallel++;
        }
    }

    // Join all the active threads to wait for them to finish working
    for (thread& t : threadPool) {
        t.join();
    }

    server->close();
    return 0;
}

/**
 * Init a signle client handling
 */
void MyParallelServer::parallelHandleClient(const int& client_socket, ClientHandler* client_handler) {
    client_handler->handleClient(client_socket);
}

/**
 * Terminate the operation of the server
 */
void MyParallelServer::close() {
    ::close(server_socket);
}


