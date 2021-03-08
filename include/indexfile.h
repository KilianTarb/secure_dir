#include "types.h"

class IndexFile {
    private:
        FileKeyCollection Collection;
    public:
        IndexFile(string name, string path);
        FileKeyCollection *GetFiles();
        string Name;
        string Path;
        bool IndexFileExists();
        bool CreateIndexFile();
        bool DeleteIndexFile();
        bool AddFile();
};
