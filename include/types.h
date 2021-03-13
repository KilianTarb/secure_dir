#include <string>
#include <vector>

using namespace std;

struct FileKey {
    char *filePath;
    char *fileName;
    char *EncyptedFileName;
};

typedef vector<FileKey> FileKeyCollection;
