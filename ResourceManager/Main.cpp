#include <experimental/filesystem>
#include <iostream>
#include <fstream>

#include "PNGLoader.h"

int main() {
	PNGLoader temp;
	Resource* resource = temp.load("Assets/testImage.png", 0);

	std::hash<std::string> test;
	std::string apa("rootfolder/tex/monkeh.apa");
	std::string apa2("rootfolder/tex/monkey.apa");

	std::cout << "Path [" << apa << "]  ID [" << test(apa) << "]." << std::endl;
	std::cout << "Path [" << apa << "]  ID [" << test(apa) << "]." << std::endl;
	std::cout << "Path [" << apa2 << "]  ID [" << test(apa2) << "]." << std::endl;
	std::cout << "Path ["<< apa2 << "]  ID ["<< test(apa2) << "]." << std::endl;

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

	//std::cout << doStuff<int>("stuff") << std::endl;
	//Mesh* data = ResourceManager::load<Mesh>();


	getchar();
	return 0;
}