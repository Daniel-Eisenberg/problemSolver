#include <iostream>
#include "CacheManger.h"
#include "Solver.h"
#include "Server.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "MySerialServer.h"


namespace boot {

    class Main {
        int main() {
            server_side::Server* server = new MySerialServer();
            Solver<string,string>* solver = new StringReverser();
            CacheManager* cacheManager = new FileCacheManager();
            return 0;
        }
    };
}




