#include <iostream>
#include "CacheManger.h"
#include "Solver.h"
#include "Server.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "MySerialServer.h"
#include "MyClientHandler.h"


int main(){

    server_side::Server* server = new MySerialServer();
    Solver<string, string>* solver = new StringReverser();
    CacheManager* cacheManager = new FileCacheManager();
    ClientHandler* clientHandler = new MyClientHandler<string,string>(solver, cacheManager);


    server->open(5600, clientHandler);
}

namespace boot {

    class Main {
        int main() {
            server_side::Server* server = new MySerialServer();
            Solver<string, string>* solver = new StringReverser();
            CacheManager* cacheManager = new FileCacheManager();
            ClientHandler* clientHandler = new MyClientHandler<string,string>(solver, cacheManager);


            server->open(5600, clientHandler);

            return 0;
        }
    };
}