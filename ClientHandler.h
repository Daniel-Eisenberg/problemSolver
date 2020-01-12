//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H

#include <ios>
class ClientHandler {

public:
    virtual void handleClient(std::istream InputStream, std::ostream OutputStream) = 0;



};







#endif //EX4_CLIENTHANDLER_H
