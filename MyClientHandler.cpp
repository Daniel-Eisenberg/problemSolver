//
// Created by Daniel Eisenberg on 12/01/2020.
//

#include <ostream>
#include <sys/socket.h>
#include <iostream>
#include <zconf.h>
#include "MyClientHandler.h"
#include "md5.h"

using namespace std;

void MyClientHandler::handleClient(int client_socket) {
    string s = "";
    char* result;
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
        if (cm.exist(s_md5)) {
            result = cm.get(s_md5)
        } else {
            result = solver.solve(s);
            cm.insert(s_md5, result);
        }

        send(client_socket, result, strlen(result), 0);
        cout << flush;
        memset(result, 0, sizeof(result));
    }

    return;
}