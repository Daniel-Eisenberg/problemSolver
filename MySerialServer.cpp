//
// Created by Daniel Eisenberg on 12/01/2020.
//

#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <zconf.h>
#include "MySerialServer.h"
#include <vector>
using namespace std;
/**
 * ---------------------TO DO----------------------
 * need time put for waiting in it needs to run i a unique thread.
 */
int MySerialServer::open(int port, ClientHandler& clientHandler) {

        int socket1 = socket(AF_INET, SOCK_STREAM, 0);
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


        //accept client
        int client_socket = accept(socket1, (struct sockaddr *) &address, (socklen_t *) &address);
        if (client_socket == -1) {
            std::cerr << "Error accepting client" << std::endl;
            return -4;
        }

        // loop condition updated by the main function

        char message[1024] = {0};
        while () {

            read(client_socket, message, 1024);
            clientHandler.handleClient(read(client_socket, message, 1024), ouputstream); //// fix outputstream!!!!!!!!!!!!!!!!!!!!!
            int i;
            string s;
            for (i = 0; i < 1024; i++) {
                if (message[i] == '\0')
                    break;
                s += message[i];
            }

        }
        close(socket1);
        //update the main thread that the thread is finished
        Tcp_Server::killServerThread(1);
        CommandUtil::cv.notify_all();
        return 0;


}



void MySerialServer::close() {

}