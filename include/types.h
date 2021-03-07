#include <string>

using namespace std;

struct IndexFile {
    string name;
    string path;
};

struct Context {
    IndexFile *index;
};

struct FileKey {
    string filePath;
    string fileName;
    string EncyptedFileName;
};