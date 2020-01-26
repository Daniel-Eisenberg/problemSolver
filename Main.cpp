#include "CacheManager.h"
#include "Solver.h"
#include "Server.h"
#include "StringReverser.h"
#include "FilesCacheManager.h"
#include "MyClientHandler.h"
#include "MyParallelServer.h"
#include "OA.h"



namespace boot {

    class Main {
    public:
        int main(int argc, char *argv[]) {
            server_side::Server *server = new MyParallelServer(11);
            Solver<string, string> *solver = new OA<string, string>();
            CacheManager<string, string> *cacheManager = new FilesCacheManager<string, string>(4);
            ClientHandler *clientHandler = new MyClientHandler(solver, cacheManager);

            int port = 5600;
            if (argc > 1)
                port = atoi(argv[1]);

            server->open(port, clientHandler);
            server->close();
            return 0;
        }
    };
}

int main(int argc, char *argv[]) {
    boot::Main().main(argc,argv);
    return 0;
}



