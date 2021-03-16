#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include "types.h"

class IndexFile {
    private:
        FileKeyCollection _collection;
        int _fileNameLength;
        ofstream _indexFileStream;
        char *_generateFileName();
        const char *_getIndexFilePath();
        bool _addToIndexFile(FileKey *file);
        bool _openIndexFileStream();
    public:
        IndexFile(string name, string path, const int fileNameLength);
        FileKeyCollection *GetFiles();
        string Name;
        string Path;
        bool IndexFileExists();
        bool CreateIndexFile();
        bool DeleteIndexFile();
        char* GetEncryptedPath(FileKey *file);
        FileKey* AddFile(char *name, char *path);
        FileKeyCollection* AddDirectory(string path);
};
