//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_SERVER_H
#define EX4_SERVER_H

#include "ClientHandler.h"

namespace server_side {

    /**
     * An interface for all the servers to implement
     */
    class Server {

    public:
        virtual int open(int port, ClientHandler* clientHandler) = 0;
        virtual void close() = 0;
        virtual ~Server() = default;
    };
}



#endif //EX4_SERVER_H
