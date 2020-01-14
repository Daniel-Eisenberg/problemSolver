//
// Created by Daniel Eisenberg on 12/01/2020.
//


#include "MySerialServer.h"

using namespace std;

int hadleclients(const int& socket, const sockaddr_in& address, const ClientHandler& client_handler);

int MySerialServer::open(int port, ClientHandler& client_handler) {


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

        thread clienthandle(hadleclients,socket1, address, client_handler);
        clienthandle.detach();
        return 0;
}



void MySerialServer::close() {
    close_server = true;
    unique_lock<std::mutex> ul(mtx);
    cv.wait(ul, []{return !close_server;});
    ::close(socket1);
}


int hadleclients(const int& socket, const sockaddr_in& address, const ClientHandler& client_handler) {
    while(!close_server) {
        struct timeval tv;
        tv.tv_sec = 2;
        setsockopt(socket1, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
        //accept client
        int client_socket = accept(socket, (struct sockaddr *) &address, (socklen_t *) &address);
        if (client_socket == -1) {
            std::cerr << "Error accepting client" << std::endl;
            return -4;
        }
        client_handler.handleClient(client_socket);
    }
    close_server = false;
    cv.notify_all();
}