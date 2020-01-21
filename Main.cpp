#include <iostream>
#include "CacheManager.h"
#include "Solver.h"
#include "Server.h"
#include "StringReverser.h"
#include "FilesCacheManager.h"
#include "MySerialServer.h"
#include "MyClientHandler.h"
#include "MyTestClientHandler.h"
#include "MyParallelServer.h"


namespace boot {

    class Main {
    public:
        int main() {
            server_side::Server* server = new MyParallelServer(3);
            Solver<string, string>* solver = new StringReverser();
            CacheManager<string,string>* cacheManager = new FilesCacheManager<string,string>(2);
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