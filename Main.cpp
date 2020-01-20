#include <iostream>
#include "CacheManager.h"
#include "Solver.h"
#include "Server.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "MySerialServer.h"
#include "MyClientHandler.h"
#include "MyTestClientHandler.h"


namespace boot {

    class Main {
    public:
        int main() {
            server_side::Server* server = new MySerialServer();
            Solver<string, string>* solver = new StringReverser();
            CacheManager<string,string>* cacheManager = new FileCacheManager();
            ClientHandler* clientHandler = new MyTestClientHandler(solver, cacheManager);

            server->open(5400, clientHandler);

            sleep(10);
            server->close();
            return 0;
        }
    };
}


int main(){
    boot::Main main;
    return main.main();
}