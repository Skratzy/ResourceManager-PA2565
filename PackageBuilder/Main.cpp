#include "FormatLoader.h"
#include "OBJReformatter.h"
#include "PNGLoader.h"
#include "JPGLoader.h"
#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include "Defines.h"
#include <ziplib/zip.h>
#include <crtdbg.h>

using namespace std::experimental::filesystem;

void zipDirectory(zip* archive, path path) {
	if (is_directory(path)) {
		directory_iterator end{};
		for (directory_iterator iter(path); iter != end; ++iter) {
			std::string zipPath = iter->path().string();
			// Convert from double back-slash to forward-slash (damnit windows...)
			std::replace(zipPath.begin(), zipPath.end(), '\\', '/');
			zipDirectory(archive, zipPath);
		}
		zip_dir_add(archive, path.string().c_str(), 0);
	}
	else if(is_regular_file(path))
	{
		std::string filePath = path.string();
		// Convert from double back-slash to forward-slash (damnit windows...)
		std::replace(filePath.begin(), filePath.end(), '\\', '/');
		zip_source* s = zip_source_file(archive, filePath.c_str(), 0, 0);
		zip_file_add(archive, filePath.c_str(), s, 0);
	}
}

void convertDirectory(path originPath, path currentPath, path targetPath, std::vector<FormatLoader*> loaders) {
		if (is_directory(currentPath)) {
			directory_iterator end{};
			for (directory_iterator iter(currentPath); iter != end; ++iter) {
				convertDirectory(originPath, iter->path(), targetPath, loaders);
			}
		}
		else if (is_regular_file(currentPath))
		{	
			std::string extension = currentPath.extension().generic_string();
			bool extensionSupported = false;
			for (auto FL : loaders) {

				if (FL->extensionSupported(extension)) {
					// Getting data as a string from file
					extensionSupported = true;
					std::string res = FL->load(currentPath.string());

					// Fix file path so that the new file is placed correctly
					std::string origin = originPath.string();
					std::string file = currentPath.parent_path().string() + "\\";
					origin = file.substr(0, origin.size());
					file.erase(0, origin.length());
					file = targetPath.string() + file;
					std::ofstream myFile;
					// Adding correct extension and creating file
					if (extension == ".obj") {
						file += currentPath.stem().string() + ".rmmesh";
						myFile.open(file);
						myFile << res;
						myFile.close();
					}
					else if (extension == ".png" || extension == ".jpg") {
						file += currentPath.stem().string() + ".rmtex";
						myFile.open(file);
						myFile << res;
						myFile.close();
					}
				}

			}
			// If no formatloader for the extension is found, add it unconverted to the directory
			if (!extensionSupported) {
				std::string copyStringPath = targetPath.string() + "\\" + currentPath.stem().string() + extension;
				path copyPath(copyStringPath);
				copy_file(currentPath, copyPath, copy_options::skip_existing);
			}
		}
}

void createPackage(path originPath, path targetPath, std::vector<FormatLoader*> loaders) {
	// Copy folder structure from original folder
	try {
		copy(originPath, targetPath.stem(), copy_options::directories_only | copy_options::recursive);
	}
	catch (std::exception e) {
		RM_DEBUG_MESSAGE("Faulty file path", 1);
	}

	// Go through original folder and convert all files that are supported and put it in the temporary folder
	convertDirectory(originPath, originPath, targetPath.stem(), loaders);

	// Zip the temporary folder
	std::string archiveName = targetPath.string() + ".zip";
	zip* archive = zip_open(archiveName.c_str(), ZIP_CREATE, 0);
	zipDirectory(archive, targetPath.stem());
	zip_close(archive);

	// Remove temporary folder
	remove_all(targetPath.stem());
}



int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	namespace fs = std::experimental::filesystem;

	// Adding loaders
	std::vector<FormatLoader*> loaders;
	loaders.push_back(new PNGLoader);
	loaders.push_back(new OBJReformatter);
	loaders.push_back(new JPGLoader);

	// Origin path and target path
	//path origin = path("../ResourceManager/testAssets");
	//path target = path("../Release/AssetPackage");
	path origin = path(argv[1]);
	path target = path(argv[2]);

	createPackage(origin, target, loaders);

	for (unsigned int i = 0; i < loaders.size(); i++) {
		delete loaders.at(i);
	}

	return 0;
}



