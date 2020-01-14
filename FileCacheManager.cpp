//
// Created by Daniel Eisenberg on 12/01/2020.
//



/**
 * USE FROM EX2!!!!
 */


#include "FileCacheManager.h"
FileCacheManager::FileCacheManager() {

}

bool FileCacheManager::exist() {

}

void FileCacheManager::pull() {

}

void FileCacheManager::save() {
    string filename = generateFilename(key, class_name);
    std::fstream file("../"+filename,ios::out|ios::binary);

    file.write( (char *) & obj, sizeof(obj));
    file.close();
    return;
}