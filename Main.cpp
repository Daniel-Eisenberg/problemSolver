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
#include "Matrix.h"
#include "BFSAlgo.h"


namespace boot {

    class Main {
    public:
        int main() {
            server_side::Server* server = new MyParallelServer(3);
            Solver<string, string>* solver = new StringReverser();
            CacheManager<string,string>* cacheManager = new FilesCacheManager<string,string>(2);
            ClientHandler* clientHandler = new MyClientHandler(solver, cacheManager);

            server->open(5400, clientHandler);

            sleep(10);
            server->close();
            return 0;
        }
    };
}


int main(){
    //boot::Main main;
    //return main.main();
    vector<vector<int>> vec = {{1,2}, {0,0}};
    Matrix* a = new Matrix(&vec);
    BFS<myPoint> t;
    std::vector<string> *str = t.search(a);

    for (auto r: *str) {
        cout << r << " ";
    }
    cout << endl;

    return 0;

}