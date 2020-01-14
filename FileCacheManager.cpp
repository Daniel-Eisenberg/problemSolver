//
// Created by Daniel Eisenberg on 12/01/2020.
//



/**
 * USE FROM EX2!!!!
 */


#include "FileCacheManager.h"
FileCacheManager::FileCacheManager() {

}

bool FileCacheManager::exist(string key) {
    std::fstream file("../"+key,ios::in|ios::binary);
    if(!file) {
        return false;
    }

    return true;
}

string FileCacheManager::get(string key) {
    std::fstream file("../"+key,ios::in|ios::binary);
    if(!file) {
        cout << "File: "  << key  << " doesnt exists" << endl;
    }

    string line,result;
    while (getline(file, line)) {
        result += line;
    }

//    file.read((char *) & obj, sizeof(obj));
    file.close();
    return result;
}

void FileCacheManager::insert(string key, string record) {
    std::fstream file("../"+key,ios::out|ios::binary);

    file.write(record.c_str(), sizeof(record));
    file.close();
    return;
}