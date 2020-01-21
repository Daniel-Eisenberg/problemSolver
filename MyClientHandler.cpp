////
//// Created by Daniel Eisenberg on 12/01/2020.
////
//
#include <ostream>
#include <sys/socket.h>
#include <iostream>
#include <zconf.h>
#include <vector>
#include "MyClientHandler.h"
#include "md5.h"
#include "MyParallelServer.h"

using namespace std;

void MyClientHandler::handleClient(int client_socket) {
    string s = ""; string matrix_str = ""; string result;
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
        matrix_str.append(s);
        matrix_str.append("\n");
    }

//    vector<vector<int>> matrix = reconstructMatrix(s);
    if (cm->isExists(matrix_str)) {
        result = cm->get(matrix_str);
    } else {
        result = string(solver->solve(matrix_str));
        cm->insert(matrix_str, result);
    }
    result += "\n";

    send(client_socket, result.c_str(), strlen(result.c_str()), 0);
    cout << flush;
    MyParallelServer::currentParallel--;
    return;
}

