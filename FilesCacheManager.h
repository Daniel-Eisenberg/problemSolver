//
// Created by Yuval Grinberg on 25/11/2019.
//


#ifndef EX2_EX2_H
#define EX2_EX2_H

#include <string>
#include <list>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <iostream>
#include <vector>
#include "CacheManager.h"

using namespace std;

class FilesManager {
public:
    FilesManager(){}

    ~FilesManager(){};

    void logFile(string key, string obj) {
        string filename = key;
        std::fstream file("../presist/"+filename,ios::out);

        file.write(obj.c_str(), sizeof(obj.c_str()));
        file.close();
        return;
    }

    string getFile(string key) {
        string filename = key;
        std::fstream file("../presist/"+filename,ios::in);
        if(!file) {
            cout << "ERROR: Open file for reading error, key doesn't exists in cache and files.";
        }

        string line,result;
        while (getline(file, line)) {
            result += line;
        }
        file.close();
        return result;
    }

    bool isFileExists(string key) {
        string filename = key;
        std::fstream file("../presist/"+filename,ios::in);
        if(!file) {
            return false;
        }
        return true;
    }
};


template <typename P>
class FilesCacheManager : public CacheManager<P,string> {
    int capacity = 0;
    std::list<std::string> lru;
    std::unordered_map <std::string, std::pair<string, std::list<std::string>::iterator>> memoryCache;
public:
    FilesCacheManager<P,string>(int capacity) {
        this->capacity = capacity;

    }

    ~FilesCacheManager(){};

    void insert(P problem, string obj) {
        string key = hashKey(problem);

        // Log object to files
        FilesManager filesManager;
        filesManager.logFile(key, obj);

        // Key not in cache
        if (this->memoryCache.find(key) == this->memoryCache.end()) {
            // If cache is full -> remove LRU element from lru list and memoryCache to free space for the new element
            if (static_cast<int>(lru.size()) == capacity) {
                string last = lru.back();
                lru.pop_back();
                this->memoryCache.erase(last);
            }
        } else // Key in cache -> free space in lru list to put the element in front
            lru.erase((std::list<std::string>::iterator) this->memoryCache[key].second);

        // Update lru list and memoryCache with the inserted element
        lru.push_front(key);
        this->memoryCache[key] = {obj, lru.begin()};
    }

    string get(P problem) {
        string obj;
        string key = hashKey(problem);
        auto item = this->memoryCache.find(key);

        // Key not in cache -> search for key in files
        if (item == this->memoryCache.end()) {
            FilesManager filesManager;
            obj = filesManager.getFile(key);

            // Cache is full -> remove LRU element from lru list and memoryCache to free space for the new element
            if (static_cast<int>(lru.size()) == capacity) {
                string last = lru.back();
                lru.pop_back();
                this->memoryCache.erase(last);
            }
        } else { // Key in cache -> free space in lru list to put the element in front
            lru.erase((std::list<std::string>::iterator) this->memoryCache[key].second);
            obj = item->second.first;
        }

        // Update lru list and cache then return the object
        lru.push_front(key);
        this->memoryCache[key] = {obj, lru.begin()};

        return obj;
    }

    bool isExists(P problem) {
        string key = hashKey(problem);
        auto item = this->memoryCache.find(key);

        // Key not in cache -> search for key in files
        if (item == this->memoryCache.end()) {
            FilesManager filesManager;
            return filesManager.isFileExists(key);
        } else
            return true;
    }

    static string hashKey(P key) {
        hash<P> stdHash = NULL;
        return md5(stdHash(key));
    }
};



#endif //EX2_EX2_H
