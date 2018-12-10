#include "FormatLoader.h"
#include "OBJLoader.h"
#include "PNGLoader.h"
#include "JPGLoader.h"
#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include "MyMesh.h"
#include "Defines.h"

using namespace std::experimental::filesystem;

void zipEntity(path path, std::vector<FormatLoader*> loaders) {
	if (is_directory(path)) {
		recursive_directory_iterator end{};
		for (recursive_directory_iterator iter(path); iter != end; ++iter) {
			zipEntity(iter->path(), loaders);
		}
		//Add directory to archive
	}
	else if(is_regular_file(path))
	{
		std::string extension = path.extension().generic_string();
		for (auto FL : loaders) {
			if (FL->extensionSupported(extension)) {
				our::string res = FL->load(path.string().c_str());//FIX GUID

				//Get loaded resource data and write to file.

				std::ofstream myfile;
				if (extension == ".obj") {
					std::string file = path.stem().string();
					file += ".mesh";
					myfile.open(file.c_str());

					//Write mesh specific data
					myfile << res;

					myfile.close();
				}


			}
		}
		//Add file to archive
	}

}


int main(int argc, char* argv[]) {
	
	namespace fs = std::experimental::filesystem;
	
	std::vector<FormatLoader*> loaders;
	loaders.push_back(new PNGLoader);
	loaders.push_back(new OBJLoader);
	loaders.push_back(new JPGLoader);

	fs::path folder = fs::path("Assets");
	zipEntity(folder, loaders);

	// TEST
	///PNGLoader asdf;
	///our::string temp = asdf.load("Assets/testImage.png");


	getchar();
	return 0;
}



