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
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include "indexfile.h"


std::string genNewFileName(const int len, int seed) {
    std::string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    srand((unsigned) seed);
    tmp_s.reserve(len);
    for (int i = 0; i < len; i++) 
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];

    return tmp_s;
}


const std::string OUTPUT_DIRECTORY_PATH = "./output";
void createOutputDirectory() {
    std::filesystem::create_directory(OUTPUT_DIRECTORY_PATH);
}


std::string createOutputFilePath(std::string fileName) {
    return OUTPUT_DIRECTORY_PATH + "/" + fileName;
}


int main(int argc, char** argv) {
    std::vector<FileKey> fileKeyPairs;

    int fileNameSeedCounter = 10;

    // Validate if args are directories
    for (int i = 1; i < argc; i++) {
        printf("Finding directory %s...", argv[i]);
        if (std::filesystem::is_directory(argv[i])) {
            printf("Found\n");

            // Iterate through files and directories
            int fileCount = 0;
            for(auto& p: std::filesystem::recursive_directory_iterator(argv[i])) {
                if (p.is_regular_file()) {
                    fileCount++;
                    fileNameSeedCounter++;

                    FileKey file;
                    file.fileName = p.path().filename();
                    file.filePath = p.path().relative_path();
                    file.EncyptedFileName = genNewFileName(24, fileNameSeedCounter);

                    fileKeyPairs.push_back(file);
                }
            }
        } else { 
            printf("Not found\n");
            return 1;
        }
    }

    std::cout << "Encrypting..." << std::endl;
    createOutputDirectory();

    /* 256 bit key */
    AES_KEY key;
    unsigned char ckey[] = "01234567890123456789012345678901";
    AES_set_encrypt_key(ckey, 128, &key);

    for (int i = 0; i < fileKeyPairs.size(); i++) {
        std::FILE *source_file;
        source_file = fopen(fileKeyPairs[i].filePath.c_str(), "r");

        std::FILE *dest_file;
        dest_file = fopen(createOutputFilePath(fileKeyPairs[i].EncyptedFileName).c_str(), "ab+");

        int b_read, b_write; 
        int current_read = 0;

        fseek(source_file, 0, SEEK_END);
        int total_read = ftell(source_file);
        rewind(source_file);
        
        // File convertion summary
        printf("%s => %s - %i bytes\n", 
            fileKeyPairs[i].fileName.c_str(), 
            fileKeyPairs[i].EncyptedFileName.c_str(), 
            total_read
        );

        while (current_read < total_read) {
            unsigned char *in_block = (unsigned char *)malloc(AES_BLOCK_SIZE);
            unsigned char *out_block = (unsigned char *)malloc(AES_BLOCK_SIZE);

            current_read += fread(in_block, 1, AES_BLOCK_SIZE, source_file);

            AES_encrypt(in_block, out_block, &key);

            b_write = fwrite(out_block, 1, AES_BLOCK_SIZE, dest_file);
        }

        fclose(source_file);
        fclose(dest_file);
    }

    return 0;
}
