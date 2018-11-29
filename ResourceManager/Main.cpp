#include <filesystem>
#include <iostream>

int main() {
	std::hash<std::string> test;
	std::string apa("rootfolder/tex/monkeh.apa");
	std::string apa2("rootfolder/tex/monkey.apa");

	std::cout << "Path [" << apa << "]  ID [" << test(apa) << "]." << std::endl;
	std::cout << "Path [" << apa << "]  ID [" << test(apa) << "]." << std::endl;
	std::cout << "Path [" << apa2 << "]  ID [" << test(apa2) << "]." << std::endl;
	std::cout << "Path ["<< apa2 << "]  ID ["<< test(apa2) << "]." << std::endl;

	getchar();
	return 0;
}