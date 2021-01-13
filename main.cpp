#include <ctime>
#include <cstdio>
#include <ostream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <unistd.h>

// Structure that contains file properties
struct fileKeyPair {
	std::string filePath;
	std::string fileName;
	std::string EncyptedFileName;
};


// Generates a random string.
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

int main(int argc, char** argv) {
	std::vector<fileKeyPair> fileKeyPairs;
	
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
					fileKeyPair file;
					file.fileName = p.path().filename();
					file.filePath = p.path().relative_path();
					file.EncyptedFileName = genNewFileName(24, fileNameSeedCounter);
					fileKeyPairs.push_back(file);
					std::cout << file.EncyptedFileName << std::endl;
				}
			}
		} else { 
			printf("Not found\n");
		}
	}
	return 0;
}
