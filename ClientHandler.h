//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H

#include <ios>
class ClientHandler {

public:
    virtual void handleClient(int socket) = 0;
    virtual ~ClientHandler() = default;
};







#endif //EX4_CLIENTHANDLER_H
