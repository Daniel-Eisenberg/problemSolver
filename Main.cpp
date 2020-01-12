#include <iostream>
#include "CacheManger.h"

namespace boot {

    class Main {
        int main() {
            Server* server = new MySerialServer();
            Solver* solver = new StringReverser();
            CacheManager* cacheManager = new FileCacheManager();
            return 0;
        }
    }
}