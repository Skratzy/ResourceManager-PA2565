#include "FormatLoader.h"
#include "OBJLoader.h"
#include "PNGLoader.h"
#include "JPGLoader.h"
#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include "MyMesh.h"
#include "Defines.h"
#include <ziplib/zip.h>
#include "removeStack.h"
#include <crtdbg.h>

using namespace std::experimental::filesystem;

void zipDirectory(zip* archive, path path) {
	if (is_directory(path)) {
		directory_iterator end{};
		for (directory_iterator iter(path); iter != end; ++iter) {
			zipDirectory(archive, iter->path());
		}
		zip_dir_add(archive, path.string().c_str(), 0);
	}
	else if(is_regular_file(path))
	{
		zip_source* s = zip_source_file(archive, path.string().c_str(), 0, 0);
		zip_file_add(archive, path.string().c_str(), s, 0);
	}
}

void convertDirectory(path path, std::vector<FormatLoader*> loaders) {
		if (is_directory(path)) {
			directory_iterator end{};
			for (directory_iterator iter(path); iter != end; ++iter) {
				convertDirectory(iter->path(), loaders);
			}
		}
		else if (is_regular_file(path))
		{	
			std::string extension = path.extension().generic_string();
			for (auto FL : loaders) {

				if (FL->extensionSupported(extension)) {
					// actual file convertion
					if (extension == ".obj") {
						// Temp code for creating a file
						std::string file = path.parent_path().string() + "\\" + path.stem().string() + ".mymesh";
						std::string origin = file.substr(0, file.find("\\", 0));
						file.erase(0, origin.length());
						file = "Package" + file;
						std::ofstream myFile;
						myFile.open(file);
						myFile << "asd";
						myFile.close();
					}
				}
				// If no supported extension are found: still add unconverted file?

			}
		}
}

void createPackage(path path, std::vector<FormatLoader*> loaders) {
	// Creating temporary folder named Package
	create_directory("Package");
	std::experimental::filesystem::path package = std::experimental::filesystem::path("Package");
	// Copy folder structure from original folder
	copy(path, package, copy_options::directories_only | copy_options::recursive);

	// Go through original folder and convert all files that are supported and put it in the temporary folder
	convertDirectory(path, loaders);

	// Zip the temporary folder
	zip* archive = zip_open("Package.zip", ZIP_CREATE, 0);
	zipDirectory(archive, package);
	zip_close(archive);

	// Remove temporary folder
	std::experimental::filesystem::remove_all(package);
}



int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	namespace fs = std::experimental::filesystem;

	std::vector<FormatLoader*> loaders;
	loaders.push_back(new PNGLoader);
	loaders.push_back(new OBJLoader);
	loaders.push_back(new JPGLoader);

	fs::path folder = fs::path("testfolder2");
	createPackage(folder, loaders);

	return 0;
}



