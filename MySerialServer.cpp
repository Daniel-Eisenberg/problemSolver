//
// Created by Daniel Eisenberg on 12/01/2020.
//


#include "MySerialServer.h"
#include "ClientHandler.h"
#include "MyClientHandler.h"

using namespace std;

int handleClients(const int& socket, const sockaddr_in& address, ClientHandler* client_handler);
/**
 * open a server in a unique thread
 * @param port for the server socket
 * @param client_handler unique object to handle the clients of the server
 * @return
 */
int MySerialServer::open(int port, ClientHandler* client_handler) {


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


/**
 * close the server thread
 */
void MySerialServer::close() {
    close_server = true;
    unique_lock<std::mutex> ul(mtx);
    cv.wait(ul, []{return !close_server;});
    ::close(socket1);
}
/**
 * @return true if the server should be closed
 */
bool MySerialServer::getCloseServer() {
    return close_server;
}
/**
 * function that runs from the server as a unique thread
 * @param socket file descriptor of the client
 * @param address
 * @param client_handler
 * @return
 */
int handleClients(const int& socket, const sockaddr_in& address, ClientHandler* client_handler) {
    while(!MySerialServer::getCloseServer()) {
        struct timeval tv;
        tv.tv_sec = 2;
        setsockopt(socket1, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
        //accept client
        int client_socket = accept(socket, (struct sockaddr *) &address, (socklen_t *) &address);
        if (client_socket == -1) {
            std::cerr << "Error accepting client" << std::endl;
            return -4;
        }
        client_handler->handleClient(client_socket);
    }
    close_server = false;
    cv.notify_all();
    return 0;
}