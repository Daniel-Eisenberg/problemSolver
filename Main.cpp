#include <iostream>
#include "CacheManager.h"
#include "Solver.h"
#include "Server.h"
#include "StringReverser.h"
#include "FilesCacheManager.h"
#include "MySerialServer.h"
#include "MyClientHandler.h"
#include "MyParallelServer.h"
#include "Matrix.h"
#include "OA.h"
#include "DFSAlgo.h"
#include "AStarAlgo.h"
#include "BestFSAlgo.h"


namespace boot {

    class Main {
    public:
        int main() {
            server_side::Server* server = new MyParallelServer(3);
            Solver<string, string>* solver = new OA<string, string>();
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
    vector<vector<int>> vec = {{1,999,100},
                               {0,5,6},
                               {1000,5,6}};
    Matrix* a = new Matrix(&vec);
//    AStarAlgo<myPoint> *t = new AStarAlgo<myPoint>();
    BestFSAlgo<myPoint> *t = new BestFSAlgo<myPoint>();
    std::vector<string> *str = t->search(a);

    for (auto r: *str) {
        cout << r << " ";
    }
    cout << endl;

    //test for OA
//    OA<string,string>* a = new OA<string,string>();
//    std::string str = "1,2,3\n4,5,6\n7,8,9\n";
//    auto m = a->reconstructMatrix(str);




    return 0;

}