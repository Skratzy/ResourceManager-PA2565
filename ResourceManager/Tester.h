#ifndef _RM_TESTER_H
#define _RM_TESTER_H

#include <string>
#include <vector>

struct object {
	std::string meshPath;
	std::string texturePaths;
};

class Tester {
private:
	void sokol(std::vector<object> objects);

public:
	Tester();
	~Tester();

	void createAZipArchive();
	void openAndHandleAssetsFromZipArchive(std::string zippedFilePath);
	void openAndHandleAssetsFromFileSystem();
	void generateAssetsToCreateGUIDSandPrintThem();
	void loadAssetsWithThreadSafety();
	void loadBelowAndAboveMaxCapacity_printUsage();
};

#endif
