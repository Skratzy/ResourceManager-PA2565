#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <crtdbg.h>

#include "ziplib/zip.h"
#include "ResourceManager.h"
#include "PNGLoader.h"
#include "JPGLoader.h"
#include "Defines.h"


void read(bool buffered) {
	std::ifstream fileStream;
	if (!buffered)
		fileStream.rdbuf()->pubsetbuf(0, 0);
	fileStream.open("test.txt");

	// get length of file:
	fileStream.seekg(0, fileStream.end);
	int length = fileStream.tellg();
	fileStream.seekg(0, fileStream.beg);

	char* buffer = new char[length];

	fileStream.read(buffer, length);

	delete[] buffer;
}

void testHash() {
	std::hash<std::string> test;
	std::string apa("rootfolder/tex/monkeh.apa");
	std::string apa2("rootfolder/tex/monkey.apa");

	std::cout << "Path [" << apa << "]  ID [" << test(apa) << "]." << std::endl;
	std::cout << "Path [" << apa << "]  ID [" << test(apa) << "]." << std::endl;
	std::cout << "Path [" << apa2 << "]  ID [" << test(apa2) << "]." << std::endl;
	std::cout << "Path [" << apa2 << "]  ID [" << test(apa2) << "]." << std::endl;
}

void testReadTextures() {
	ResourceManager& manager = ResourceManager::getInstance();
	manager.registerFormatLoader(RM_NEW(PNGLoader));
	manager.registerFormatLoader(RM_NEW(JPGLoader));

	Resource* png = manager.load("Assets/testImage.png");
	Resource* jpg = manager.load("Assets/testImage1.jpg");
	// Breakpoint and look at image
}

void bufferedUnbufferedTiming() {
	auto start = std::chrono::high_resolution_clock::now();
	read(true);
	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;

	start = std::chrono::high_resolution_clock::now();
	read(true);
	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;
}

void readFileInZip(const char* zipPath, const char* filePath)
{
	int err = 0;
	zip* archive = zip_open(zipPath, 0, &err);
	zip_stat_t* stat = new zip_stat_t;
	zip_stat_init(stat);
	zip_stat(archive, filePath, ZIP_FL_NOCASE | ZIP_FL_NODIR, stat);
	zip_file* fileUncompressed = zip_fopen(archive, filePath, 0);
	auto length = stat->size;
	char* buffer = new char[length + 1];
	zip_fread(fileUncompressed, buffer, length);
	buffer[length] = '\0';
	std::cout << buffer << std::endl;

	delete[] buffer;
	delete stat;
	zip_fclose(fileUncompressed);
	zip_close(archive);
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	testReadTextures();
	getchar();
	return 0;
}