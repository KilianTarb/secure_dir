#pragma once
#include <filesystem>
#include "types.h"

class IndexFile {
    private:
        FileKeyCollection _collection;
        int _fileNameLength;
        char *_generateFileName();
        bool _addToIndexFile(FileKey *file);
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
