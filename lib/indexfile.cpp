#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include "indexfile.h"

using namespace std;

/**
 * @brief Construct a new Index File:: Index File object
 * 
 * @param name 
 * Name of the index file.
 * @param path 
 * Path of the index file AND encrypted files.
 * @param fileNameLength 
 * Amount of alphanumeric characters in the file names.
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
FileKeyCollection* IndexFile::GetFiles() {
    return &_collection;
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
FileKey* IndexFile::AddFile(char *name, char *path) {
    FileKey fk;

    fk.fileName = (char *)malloc(sizeof(name));
    strcpy(fk.fileName, name);

    fk.filePath = (char *)malloc(sizeof(path));
    strcpy(fk.filePath, path);

    fk.EncyptedFileName  =_generateFileName();

    _collection.push_back(fk);
    return &_collection[_collection.size()-1];
}

/**
 * @brief Add all files in a directory recursively. Return NULL if directory not found.
 * 
 * @param path 
 * @return FileKeyCollection* 
 */
FileKeyCollection* IndexFile::AddDirectory(string path) {
    if (filesystem::is_directory(path)) {
        for(auto& p: filesystem::recursive_directory_iterator(path)) {
            if (p.is_regular_file()) {
                AddFile((char *)p.path().filename().c_str(), (char *)p.path().relative_path().c_str());
            }
        }
        return &_collection;
    }
    return NULL;
}

/**
 * @brief Return the output path for a file.
 * 
 * @param file 
 * FileKey struct
 * @return const char* 
 */
const char* IndexFile::GetEncryptedPath(FileKey *file) {
    return (Path + "/" + (string)file->EncyptedFileName).c_str();
}

/**
 * @brief Generate a new pseudo-random name for the encrypted file.
 * 
 * @return pseudo-random name
 */
char *IndexFile::_generateFileName() {
    int seed = _collection.size()+1;
    char tmp[_fileNameLength];
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    srand((unsigned) seed);

    for (int i = 0; i < _fileNameLength+1; i++)
        tmp[i] = alphanum[rand() % (sizeof(alphanum) - 1)]; 

    char *returnVal = (char *)malloc(sizeof(tmp));
    strcpy(returnVal, tmp);
    return returnVal;
}
