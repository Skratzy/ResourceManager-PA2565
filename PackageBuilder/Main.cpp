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

using namespace std::experimental::filesystem;

void zipEntity(zip* archive, path path, std::vector<FormatLoader*> loaders) {
	if (is_directory(path)) {
		zip_dir_add(archive, path.generic_string().c_str(), 0);
		recursive_directory_iterator end{};
		for (recursive_directory_iterator iter(path); iter != end; ++iter) {
			zipEntity(archive, iter->path(), loaders);
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

					//zip_source* s = zip_source_buffer(archive, &res, sizeof(res), 0);
					zip_source* s = zip_source_file(archive, path.string().c_str(), 0, 0);
					int index = zip_file_add(archive, file.c_str(), s, 0);
					
					//myfile.open(file.c_str());

					////Write mesh specific data
					//myfile << res;

					//myfile.close();
					
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

	//fs::path folder = fs::path("Assets");
	//zipEntity(folder, loaders);

	//OBJLoader* obj = new malloc(sizeof(OBJLoader)) OBJLoader;



	//loaders.emplace_back(new OBJLoader);
	//loaders.back()->m_supportedExtensions.push_back("obj");
	//loaders.back()->setExtension("obj");

	//fs::path folder = fs::path(argv[0]);
	//fs::path folder = fs::path("C:/Users/enukp/source/repos/Skratzy/ResourceManager/PackageBuilder/testfolder");

	fs::path folder = fs::path("testfolder");

	int err = 0;
	zip* archive = zip_open("C:/Users/enukp/source/repos/Skratzy/ResourceManager/PackageBuilder/testarchive.zip", ZIP_CREATE, &err);



	//zip_dir_add(archive, "C:/Users/enukp/source/repos/Skratzy/ResourceManager/PackageBuilder/testfolder3.zip", 0);

	zipEntity(archive, folder, loaders);
	zip_close(archive);


	getchar();
	return 0;
}



