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
    srand(time(NULL));
    vector<vector<int>> vec;
    for (int i = 0; i < 15; i++) {
        vector<int> tmpvec;
        for (int j = 0; j < 15; j++) {
            tmpvec.push_back(rand() % 21);
        }
        vec.push_back(tmpvec);
    }
    vector<vector<int>> vec1 = vec;
    vector<vector<int>> vec2 = vec;
    vector<vector<int>> vec3 = vec;

    auto a = new Matrix(&vec);
    auto b = new Matrix(&vec1);
    auto c = new Matrix(&vec2);
    auto d = new Matrix(&vec3);
    auto t = new DFSAlgo<myPoint>();
    auto t1 = new BFS<myPoint>();
    auto t2 = new AStarAlgo<myPoint>();
    auto t3 = new BestFSAlgo<myPoint>();


    std::vector<string> *str = t->search(a);
    std::vector<string> *str1 = t1->search(b);
    std::vector<string> *str2 = t2->search(c);
    std::vector<string> *str3 = t3->search(d);


    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec.size(); j++) {
            cout << vec.at(i).at(j) << ", ";
        }
        cout << endl;
    }

    cout << "BFS " << b->nodesEvaluated << endl;
    cout << "DFS " << a->nodesEvaluated << endl;
    cout << "BestFS " << d->nodesEvaluated << endl;
    cout << "Astar " << c->nodesEvaluated << endl;

//    for (auto s : *str2) {
//        cout << s << ",";
//    }
//    for (auto s : *str2) {
//        cout << s << ",";
//    }



    //test for OA
//    OA<string,string>* a = new OA<string,string>();
//    std::string str = "1,2,3\n4,5,6\n7,8,9\n";
//    auto m = a->reconstructMatrix(str);




    return 0;

}