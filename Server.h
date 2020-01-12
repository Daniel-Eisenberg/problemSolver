//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_SERVER_H
#define EX4_SERVER_H

#include "ClientHandler.h"

namespace server_side {

    class Server {

    public:
        virtual int open(int port, ClientHandler& clinethandler) = 0;
        virtual int close() = 0;

    };
}



#endif //EX4_SERVER_H
