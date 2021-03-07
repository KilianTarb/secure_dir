#include <iostream>
#include <sys/stat.h>
#include "indexfile.h"

bool IndexFileExists(Context *c) {
    struct stat buf;
    return (stat(c->index->name.c_str(), &buf) == 0);
}

bool CreateIndexFile(Context *c) {
    FILE *f = fopen(c->index->path.c_str(), "w");
    if (f != NULL)
        if (fclose(f) == 0)
            return true;
    return false;
}

bool DeleteIndexFile(Context *c) {
    return (remove(c->index->path.c_str()) == 0);
}