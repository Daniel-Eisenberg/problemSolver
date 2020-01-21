//
// Created by Daniel Eisenberg on 12/01/2020.
//



/**
 * USE FROM EX2!!!!
 */


#include "FileCacheManager.h"

/**
 * Construct the cache manager, init a map to quickly check if a key exists
 */
FileCacheManager::FileCacheManager() {
    memoryCache = new unordered_map <std::string, bool>;
}

/**
 * Check if key exists, first in the memory map, and then in files
 * @param key
 * @return
 */
bool FileCacheManager::isExists(string key) {
    if (memoryCache->count(key) > 0)
        return true;

    std::fstream file("../presist/"+key,ios::in);
    if(!file) {
        return false;
    }

    return true;
}

/**
 * Get the contents of a file
 * @param key
 * @return
 */
string FileCacheManager::get(string key) {
    std::fstream file("../presist/"+key,ios::in);
    if(!file) {
        cout << "File: "  << key  << " doesnt exists" << endl;
        return "";
    }

    string line,result;
    while (getline(file, line)) {
        result += line;
    }
    file.close();
    return result;
}

/**
 * Insert a record to a new file
 * @param key
 * @param record
 */
void FileCacheManager::insert(string key, string record) {
    std::fstream file("../presist/"+key,ios::out);

    file.write(record.c_str(), sizeof(record));
    file.close();

    memoryCache->insert({key,true});
    return;
}