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
#include <sys/stat.h>
#include "CacheManager.h"
#include "md5.h"

using namespace std;

template <typename P, typename S>
class FilesManager {
public:
    FilesManager(){}

    ~FilesManager(){};

    void logFile(P key, S solution) {
        string filename = key + ".txt";
        std::fstream file("../"+filename,ios::out);

        file << solution;
        file.close();
        return;
    }

    string getFile(P key) {
        string filename = key + ".txt";
        std::fstream file("../"+filename,ios::in);
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

    bool isFileExists(P key) {
        string filename = key + ".txt";
        std::fstream file("../"+filename,ios::in);
        if(!file) {
            return false;
        }
        return true;
    }
};

/**
 * A files cache manager that uses LRU logic
 * @tparam P
 * @tparam S
 */
template <typename P, typename S>
class FilesCacheManager : public CacheManager<P,S> {
    int capacity = 0;
    std::list<std::string> lru;
    std::unordered_map <std::string, std::pair<string, std::list<std::string>::iterator>> memoryCache;
    std::mutex mtx_cm;
public:
    FilesCacheManager<P,string>(int capacity) {
        this->capacity = capacity;
    }

    ~FilesCacheManager(){};

    /**
     * Insert new data into the cache manager
     * @param problem
     * @param solution
     */
    void insert(P problem, S solution) {
        mtx_cm.try_lock();
        string key = hashKey(problem);

        // Log object to files
        FilesManager<P,S> filesManager;
        filesManager.logFile(key, solution);

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
        this->memoryCache[key] = {solution, lru.begin()};
        mtx_cm.unlock();
    }

    /**
     * Get a sulotion from the cache manager
     * @param problem
     * @return
     */
    S get(P problem) {
        mtx_cm.try_lock();
        string solution;
        string key = hashKey(problem);
        auto item = this->memoryCache.find(key);

        // Key not in cache -> search for key in files
        if (item == this->memoryCache.end()) {
            FilesManager<P,S> filesManager;
            solution = filesManager.getFile(key);

            // Cache is full -> remove LRU element from lru list and memoryCache to free space for the new element
            if (static_cast<int>(lru.size()) == capacity) {
                string last = lru.back();
                lru.pop_back();
                this->memoryCache.erase(last);
            }
        } else { // Key in cache -> free space in lru list to put the element in front
            lru.erase((std::list<std::string>::iterator) this->memoryCache[key].second);
            solution = item->second.first;
        }

        // Update lru list and cache then return the object
        lru.push_front(key);
        this->memoryCache[key] = {solution, lru.begin()};
        mtx_cm.unlock();

        return solution;
    }

    /**
     * Check if solution exists for the problem
     * @param problem
     * @return
     */
    bool isExists(P problem) {
        mtx_cm.try_lock();
        string key = hashKey(problem);
        auto item = this->memoryCache.find(key);

        // Key not in cache -> search for key in files
        if (item == this->memoryCache.end()) {
            FilesManager<P,S> filesManager;
            bool isFileExists = filesManager.isFileExists(key);
            mtx_cm.unlock();
            return isFileExists;
        } else {
            mtx_cm.unlock();
            return true;
        }
    }

    /**
     * Hash the problem using a MD5 library, to create a unique identifier key
     * @param key
     * @return
     */
    static string hashKey(P key) {
        return md5(key);
    }
};



#endif //EX2_EX2_H
