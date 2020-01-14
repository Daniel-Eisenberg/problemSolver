//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_CACHEMANGER_H
#define EX4_CACHEMANGER_H

#include <string>
#include <list>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <iostream>

using namespace std;

class CacheManager{
    std::unordered_map <std::string, bool> memoryCache;
public:
    CacheManager(){};
    virtual ~CacheManager(){};

    virtual bool exist(string key) = 0;
    virtual string get(string key) = 0;
    virtual void insert(string key, string record) = 0;

};


#endif //EX4_CACHEMANGER_H
