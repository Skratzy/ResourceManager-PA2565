#include <experimental/filesystem>
#include <iostream>
#include <fstream>

#include "PNGLoader.h"
#include "Defines.h"
#include <crtdbg.h>

void unbufferedRead() {
	std::ifstream fileStream;
	fileStream.rdbuf()->pubsetbuf(0, 0);
	fileStream.open("test.txt");

	// get length of file:
	fileStream.seekg(0, fileStream.end);
	int length = fileStream.tellg();
	fileStream.seekg(0, fileStream.beg);

	char* buffer = new char[length];

	fileStream.read(buffer, length);
	std::string data(buffer, length);

	std::cout << data << std::endl;
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

void readImage() {
	PNGLoader loader;
	Resource* imageResource = loader.load("Assets/testImage.png", 0);
	// Breakpoint and look at image
	delete imageResource;
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	readImage();

	getchar();
	return 0;
}