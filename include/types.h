#include <string>
#include <vector>

using namespace std;

struct FileKey {
    string filePath;
    string fileName;
    string EncyptedFileName;
};

typedef vector<FileKey> FileKeyCollection;
