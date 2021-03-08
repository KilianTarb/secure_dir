#include <iostream>
#include <sys/stat.h>
#include "indexfile.h"

IndexFile::IndexFile(string name, string path) {
    IndexFile::Name = name;
    IndexFile::Path = path;
}

FileKeyCollection *IndexFile::GetFiles() {
    FileKeyCollection *collectionPtr = &Collection;
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
