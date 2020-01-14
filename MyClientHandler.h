//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H

#include <ostream>
#include <sys/socket.h>
#include <iostream>
#include <zconf.h>
#include "MyClientHandler.h"
#include "md5.h"
#include "ClientHandler.h"
#include "CacheManger.h"
#include "Solver.h"

template <typename P,typename S>
class MyClientHandler : public ClientHandler {
    Solver<P, S>* solver;
    CacheManager* cm;
public:
    MyClientHandler(Solver<P, S>* solver, CacheManager* cm) {
        this->solver = solver;
        this->cm = cm;
    }
    virtual void handleClient(int client_socket) {
        string s = "";
        string result;
        char message[1024] = {0};

        while (true) {
            read(client_socket, message, 1024);
            for (int i = 0; i < 1024; i++) {
                if (message[i] == '\0')
                    break;
                s += message[i];
            }

            if (s == "end")
                break;

            string s_md5 = md5(s);
            if (cm->exist(s_md5)) {
                result = cm->get(s_md5);
            } else {
                result = string(solver->solve(s));
                cm->insert(s_md5, result);
            }


            send(client_socket, result.c_str(), strlen(result.c_str()), 0);
            cout << flush;
        }

        return;
    }

};


#endif //EX4_MYTESTCLIENTHANDLER_H
