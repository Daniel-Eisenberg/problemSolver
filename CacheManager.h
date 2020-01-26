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

/**
 * Cache manager interface
 * @tparam P
 * @tparam S
 */
template <typename P, typename S>
class CacheManager{
    std::unordered_map <std::string, bool> memoryCache;
public:
    CacheManager(){};
    virtual ~CacheManager(){};

    virtual bool isExists(P problem) = 0;
    virtual string get(P problem) = 0;
    virtual void insert(P problem, S obj) = 0;

};


#endif //EX4_CACHEMANGER_H
