#include "FormatLoader.h"
#include <ziplib/zip.h>
#include <fstream>
#include <experimental/filesystem>


std::string FormatLoader::extractFile(const char* path, size_t check) {
	// substrings for parts of the path
	std::experimental::filesystem::path filePath(path);
	std::string zipPath = filePath.string();
	// Convert from double back-slash to forward-slash (damnit windows...)
	std::replace(zipPath.begin(), zipPath.end(), '\\', '/');
	std::string zipLocation = zipPath.substr(0, check + 4);
	std::string pathInPackage = zipPath.substr(check + 5, zipPath.length());
	std::string fileName = filePath.filename().string();
	// Opening and extracting asset from package
	int error = 0;
	zip* archive = zip_open(zipLocation.c_str(), 0, &error);
	if (!archive)
		RM_DEBUG_MESSAGE("Error while trying to open zip archive: " + zipLocation, 1);


	auto index = zip_name_locate(archive, pathInPackage.c_str(), 0);
	zip_stat_t stat;
	zip_stat_index(archive, index, 0, &stat);
	void* buffer = malloc(static_cast<size_t>(stat.size));
	zip_file* file = zip_fopen(archive, pathInPackage.c_str(), 0);
	if (!file)
		RM_DEBUG_MESSAGE("Libzip error: (" + std::string(zip_strerror(archive)) + ") on path: (" + pathInPackage + ").", 1);

	zip_fread(file, buffer, stat.size);

	std::ofstream aFile;
	aFile.open(fileName.c_str(), std::ios::out | std::ios::binary);
	aFile.write((char*)buffer, stat.size);
	aFile.close();
	zip_fclose(file);
	zip_close(archive);
	free(buffer);

	zipPath = fileName;
	return zipPath;
}

void* FormatLoader::readFile(const char* path, size_t check) {
	// substrings for parts of the path
	std::experimental::filesystem::path filePath(path);
	std::string zipPath = filePath.string();
	// Convert from double back-slash to forward-slash (damnit windows...)
	//std::replace(zipPath.begin(), zipPath.end(), '\\', '/');
	std::string zipLocation = zipPath.substr(0, check + 4);
	std::string pathInPackage = zipPath.substr(check + 5, zipPath.length());
	// Opening and extracting asset from package
	zip* archive = zip_open(zipLocation.c_str(), 0, 0);
	if (!archive)
		RM_DEBUG_MESSAGE("Error while trying to open zip archive: " + zipLocation, 1);

	auto index = zip_name_locate(archive, pathInPackage.c_str(), 0);
	zip_stat_t stat;
	zip_stat_index(archive, index, 0, &stat);
	void* buffer = malloc(static_cast<size_t>(stat.size));
	zip_file* file = zip_fopen(archive, pathInPackage.c_str(), 0);
	if (!file)
		RM_DEBUG_MESSAGE("Libzip error: (" + std::string(zip_strerror(archive)) + ") on path: (" + pathInPackage + ").", 1);

	zip_fread(file, buffer, stat.size);
	zip_fclose(file);
	zip_close(archive);
	return buffer;
}