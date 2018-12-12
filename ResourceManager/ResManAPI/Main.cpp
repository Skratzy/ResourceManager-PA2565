//#include <experimental/filesystem>
//#include <iostream>
//#include <fstream>
//#include <crtdbg.h>
//
//#include "ziplib/zip.h"
//#include "ResourceManager.h"
//#include "FormatLoaders/PNGLoader.h"
//#include "FormatLoaders/JPGLoader.h"
//#include "../Defines.h"
//#include "ResourceManager.h"
//
//#include "OBJLoader.h"
//
//	// get length of file:
//	fileStream.seekg(0, fileStream.end);
//	unsigned int length = static_cast<unsigned int>(fileStream.tellg());
//	fileStream.seekg(0, fileStream.beg);
//
//	char* buffer = new char[length];
//
//	fileStream.read(buffer, length);
//
//	delete[] buffer;
//}
//
//void testHash() {
//	std::hash<std::string> test;
//	std::string apa("rootfolder/tex/monkeh.apa");
//	std::string apa2("rootfolder/tex/monkey.apa");
//
//	std::cout << "Path [" << apa << "]  ID [" << test(apa) << "]." << std::endl;
//	std::cout << "Path [" << apa << "]  ID [" << test(apa) << "]." << std::endl;
//	std::cout << "Path [" << apa2 << "]  ID [" << test(apa2) << "]." << std::endl;
//	std::cout << "Path [" << apa2 << "]  ID [" << test(apa2) << "]." << std::endl;
//}
//
//void testReadTextures() {
//	ResourceManager& manager = ResourceManager::getInstance();
//	manager.registerFormatLoader(RM_NEW(PNGLoader));
//	manager.registerFormatLoader(RM_NEW(JPGLoader));
//
//	Resource* png = manager.load("Assets/testImage.png");
//	Resource* jpg = manager.load("Assets/testImage1.jpg");
//	// Breakpoint and look at image
//}
//
//void testOBJLoader(std::string filepath)
//{
//	OBJLoader myOBJLoader;
//
//	myOBJLoader.load(filepath, 1);
//}
//
//void readFileInZip(const char* zipPath, const char* filePath)
//{
//	int err = 0;
//	zip* archive = zip_open(zipPath, 0, &err);
//	zip_stat_t* stat = new zip_stat_t;
//	zip_stat_init(stat);
//	zip_stat(archive, filePath, ZIP_FL_NOCASE | ZIP_FL_NODIR, stat);
//	zip_file* fileUncompressed = zip_fopen(archive, filePath, 0);
//	unsigned int length = static_cast<unsigned int>(stat->size);
//	char* buffer = new char[length + 1];
//	zip_fread(fileUncompressed, buffer, length);
//	buffer[length] = '\0';
//	std::cout << buffer << std::endl;
//
//	delete[] buffer;
//	delete stat;
//	zip_fclose(fileUncompressed);
//	zip_close(archive);
//}
//

#include "../ResourceManager/Tester.h"
#include "../ResourceManager/RMTextureLoader.h"

int main() {
	Tester bot;
	RMTextureLoader loadTester;

	loadTester.load("", 0);
	bot.openAndHandleAssetsFromZipArchive("zippedFile.zip");
	return 0;
}