//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H


/**
 * USE FROM EX2!!!!
 */



#include "CacheManager.h"

class FileCacheManager : public CacheManager<string,string>{
    std::unordered_map <std::string, bool>* memoryCache;
public:
    FileCacheManager();
    ~FileCacheManager(){};

    virtual bool isExists(string key);
    virtual string get(string key);
    virtual void insert(string key, string record);

};


#endif //EX4_FILECACHEMANAGER_H
