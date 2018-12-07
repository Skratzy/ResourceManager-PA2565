#include "FormatLoader.h"
#include "OBJLoader.h"
#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include "MyMesh.h"

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
				Resource* res = FL->load(path.string().c_str(), 1);//FIX GUID

				//Get loaded resource data and write to file.

				std::ofstream myfile;
				if (extension == ".obj") {
					MyMesh* mesh = reinterpret_cast<MyMesh*>(res);
					std::string file = path.stem().string();
					file += ".mesh";
					myfile.open(file.c_str());

					//Write mesh specific data
					myfile << mesh->vertices.size();

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

	//std::vector<Resource*> resources;

	OBJLoader* obj;

	loaders.emplace_back(obj);

	fs::path folder = fs::path(argv[0]);


	zipEntity(folder, loaders);
	
	getchar();


	return 0;
}



