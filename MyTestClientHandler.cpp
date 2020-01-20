//
// Created by Daniel Eisenberg on 12/01/2020.
//

#include <ostream>
#include <sys/socket.h>
#include <iostream>
#include <zconf.h>
#include "MyTestClientHandler.h"

using namespace std;

void MyTestClientHandler::handleClient(int client_socket) {
    string s = "";
    string result;
    char message[1024] = {0};

    while (true) {
        read(client_socket, message, 1024);
        s = "";
        for (int i = 0; i < 1024; i++) {
            if (message[i] == '\0' || message[i] == '\r' || message[i] == '\n' )
                break;
            s += message[i];
        }
        if (s == "end")
            break;

        if (cm->isExists(s)) {
            result = cm->get(s);
        } else {
            result = string(solver->solve(s));
            cm->insert(s, result);
        }
        result += "\n";

        send(client_socket, result.c_str(), strlen(result.c_str()), 0);
        cout << flush;
    }
}