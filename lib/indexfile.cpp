#include <iostream>
#include <sys/stat.h>
#include "indexfile.h"

using namespace std;

/**
 * @brief Construct a new Index File:: Index File object
 * 
 * @param name 
 * @param path 
 * @param fileNameLength 
 */
IndexFile::IndexFile(string name, string path, int fileNameLength) {
    Name = name;
    Path = path;
    _fileNameLength = fileNameLength;
}

/**
 * @brief Returns pointer to the currnet collection for files.
 * 
 * @return FileKeyCollection* 
 */
FileKeyCollection *IndexFile::GetFiles() {
    FileKeyCollection *collectionPtr = &_collection;
    return collectionPtr;
}

/**
 * @brief Returns true if the index file 
 * 
 * @return true 
 * @return false 
 */
bool IndexFile::IndexFileExists() {
    struct stat buf;
    return (stat(Path.c_str(), &buf) == 0);
}

/**
 * @brief Creates the index file.
 * 
 * @return true 
 * @return false 
 */
bool IndexFile::CreateIndexFile() {
    FILE *f = fopen(Path.c_str(), "w");
    if (f != NULL)
        if (fclose(f) == 0)
            return true;
    return false;
}

/**
 * @brief Deletes the index file itself.
 * 
 * @return true 
 * @return false 
 */
bool IndexFile::DeleteIndexFile() {
    return (remove(Path.c_str()) == 0);
}

/**
 * @brief Adds a file entry to the index file.
 * 
 * @param file file struct
 * @return true 
 * @return false 
 */
FileKey* IndexFile::AddFile(string name, string path) {
    FileKey fk;
    fk.fileName = name;
    fk.filePath = path;
    fk.EncyptedFileName = _generateFileName();

    _collection.push_back(fk);
    return &fk;
}

/**
 * @brief Generate a new pseudo-random name for the encrypted file.
 * 
 * @return pseudo-random name
 */
string IndexFile::_generateFileName() {
    int seed = _collection.size();
    string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    srand((unsigned) seed);
    tmp_s.reserve(_fileNameLength);
    for (int i = 0; i < _fileNameLength; i++) 
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];

    return tmp_s;
}
