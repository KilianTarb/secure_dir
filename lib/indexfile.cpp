#include <iostream>
#include <sys/stat.h>
#include "indexfile.h"

using namespace std;

IndexFile::IndexFile(string name, string path, int fileNameLength) {
    Name = name;
    Path = path;
    _fileNameLength = fileNameLength;
}

FileKeyCollection *IndexFile::GetFiles() {
    FileKeyCollection *collectionPtr = &_collection;
    return collectionPtr;
}

bool IndexFile::IndexFileExists() {
    struct stat buf;
    return (stat(Path.c_str(), &buf) == 0);
}

bool IndexFile::CreateIndexFile() {
    FILE *f = fopen(Path.c_str(), "w");
    if (f != NULL)
        if (fclose(f) == 0)
            return true;
    return false;
}

bool IndexFile::DeleteIndexFile() {
    return (remove(Path.c_str()) == 0);
}

bool IndexFile::AddFile() {
    return false;
}

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
