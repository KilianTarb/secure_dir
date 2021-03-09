#include "types.h"

class IndexFile {
    private:
        FileKeyCollection _collection;
        int _fileNameLength;
        string _generateFileName();
    public:
        IndexFile(string name, string path, const int fileNameLength);
        FileKeyCollection *GetFiles();
        string Name;
        string Path;
        bool IndexFileExists();
        bool CreateIndexFile();
        bool DeleteIndexFile();
        FileKey* AddFile(string name, string path);
};
