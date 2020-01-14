//
// Created by Daniel Eisenberg on 12/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H


/**
 * USE FROM EX2!!!!
 */



#include "CacheManger.h"

class FileCacheManager : CacheManager{
    string presist;
public:
    FileCacheManager();
    ~FileCacheManager();

    virtual bool exist(string key);
    virtual void pull(string key);
    virtual void save(string key, string record);

};


#endif //EX4_FILECACHEMANAGER_H
