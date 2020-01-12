//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_CACHEMANGER_H
#define EX4_CACHEMANGER_H

#include <string>

using namespace std;

class CacheManager{


public:
    virtual bool exist(string record) = 0;
    virtual void pull(string record) = 0;
    virtual void save(string record) = 0;



};


#endif //EX4_CACHEMANGER_H
