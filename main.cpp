#include <ctime>
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <vector>
#include <filesystem>
#include <unistd.h>
#include "indexfile.h"
#include "AesEnc.h"

const std::string OUTPUT_DIRECTORY_PATH = "./output";
void createOutputDirectory() {
    std::filesystem::create_directory(OUTPUT_DIRECTORY_PATH);
}


std::string createOutputFilePath(std::string fileName) {
    return OUTPUT_DIRECTORY_PATH + "/" + fileName;
}

void *print_file_callback(FileKey *file) {
    printf("%s => %s\n", file->fileName, file->EncyptedFileName);
    return NULL;
}

int main(int argc, char** argv) {
    IndexFile index("index", "./output", 20);

    // Validate if args are directories
    for (int i = 1; i < argc; i++) {
        printf("Finding directory %s...\n", argv[i]);
        if (std::filesystem::is_directory(argv[i]))
            index.AddDirectory(argv[i]);
        else
            printf("%s is not a directory, skipping...\n", argv[i]);
    }

    std::cout << "Encrypting..." << std::endl;
    createOutputDirectory();


    //AesEnc enc(&index, (unsigned char *)"123123123123123213", 128);
    AesEnc enc(&index, (unsigned char *)"123123123123123213", 128);
    enc.StartEncryption(NULL, &print_file_callback);
    
    return 0;
}
