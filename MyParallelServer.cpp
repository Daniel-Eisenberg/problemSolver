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
    if (socket_parallel == -1) {
        std::cerr << "Could not create server socket" << std::endl;
        return -1;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // bind
    if (::bind(socket_parallel, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an ip" << std::endl;
        return -2;
    }

    //socket listen to port
    if (listen(socket_parallel, 1) == -1) {
        std::cerr << "Error during listening" << std::endl;
        return -3;
    }

    thread clienthandle(handleClients, socket_parallel, address, client_handler);
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
int MyParallelServer::handleClients(const int& socket, const sockaddr_in& address, ClientHandler* client_handler) {
    vector<thread> threadPool;
    bool timeout = false;
    while(!MyParallelServer::getCloseServer()) {
        if (currentParallel > maxParallel)
            continue;
        struct timeval tv;
        tv.tv_sec = 2;
        setsockopt(socket_parallel, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
        //accept client
        int client_socket = accept(socket_parallel, (struct sockaddr *) &address, (socklen_t *) &address);
        if (client_socket < 0) {
            std::cerr << "Error accepting client" << std::endl;

            if (errno == EWOULDBLOCK)
                return -4;
        } else {
            threadPool.push_back(thread(parallelHandleClient, client_socket, client_handler));
            currentParallel++;
        }
    }

    // Detach all the active threads
    for (int i = 0; i < threadPool.size(); ++i) {
        threadPool.at(i).join();
    }

    close_server_par = false;
    cv_par.notify_all();
    return 0;
}

/**
 * Init a signle client handling
 */
void MyParallelServer::parallelHandleClient(const int& client_socket, ClientHandler* client_handler) {
    client_handler->handleClient(client_socket);
}

/**
 * This method will use unique lock to terminate the operation of the server
 */
void MyParallelServer::close() {
    close_server_par = true;
    unique_lock<std::mutex> ul(mtx_par);
    cv_par.wait(ul, []{return !close_server_par;});
    ::close(socket_parallel);
}

/**
 * Getter of close_server_par
 * @return close_server_par
 */
bool MyParallelServer::getCloseServer() {
    return close_server_par;
}


