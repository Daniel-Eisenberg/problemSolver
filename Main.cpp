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
#include "BFS.h"


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
    //boot::Main main;
    //return main.main();
    vector<vector<int>> vec = {{3,2,3}, {3,2,0}, {3,3,3}};
    Matrix* a = new Matrix(&vec);
    BFS<myPoint> t;
    std::vector<string> *str = t.search(a);

    for (auto r: *str) {
        cout << r << " ";
    }
    cout << endl;



//    myPoint *a = new myPoint(0,0,0);
//    myPoint *b = new myPoint(0,0,0);
//    State<myPoint>* s1 = new State<myPoint>(a, 0, nullptr);
//    State<myPoint>* s2 = new State<myPoint>(b, 0, nullptr);
//    if (*a == *b)
//        cout << "yes";
//    if (*s1 == *s2)
//        cout << " no";

    return 0;

}