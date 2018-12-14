#include "../../Defines.h"
#include "RMMeshLoader.h"

#include "../Resources/MeshResource.h"
#include <fstream>
#include <sstream>

#include <map>
#include <unordered_map>

Resource* RMMeshLoader::load(const char* path, const long GUID)
{
	// MeshResource Variables
	/// ----------------------------------------
	int numberOfVertices;
	int numberOfIndices;
	std::vector<float> verticesData;
	std::vector<uint32_t> indices;
	/// ----------------------------------------

	//Check if asset is in package
	std::string filePath = path;
	size_t check = 0;
	check = filePath.find(".zip");
	bool loadZipped = false;
	if (check < filePath.length()) {
		loadZipped = true;
	}

	// STEP 1: LOAD THE 'RMMesh' FILE
	if (!loadZipped) {
		std::ifstream inputFile;
		inputFile.open(path);


		if (!inputFile.is_open())
			RM_DEBUG_MESSAGE("ERROR: File could not be opened: " + std::string(path), 1);

		std::string tempString;
		// # OF VERTICES
		std::getline(inputFile, tempString);
		numberOfVertices = std::stoi(tempString);
		// # OF INDICES
		std::getline(inputFile, tempString);
		numberOfIndices = std::stoi(tempString);

		verticesData.resize(numberOfVertices * 8);
		for (int i = 0; i < verticesData.size(); i++) // ORDER: p.X, p.Y, p.Z, n.X, n.Y, n.Z, U, V
		{
			std::getline(inputFile, tempString, ',');
			verticesData.at(i) = std::stof(tempString);
		}

		indices.resize(numberOfIndices);
		for (int i = 0; i < indices.size(); i++)
		{
			std::getline(inputFile, tempString, ',');
			indices.at(i) = std::stoi(tempString);
		}
	}
	else {
		void* ptr = readFile(path, check);
		std::string tempString = (char*)ptr;
		std::stringstream inputFile;
		inputFile << tempString;
		// # OF VERTICES
		std::getline(inputFile, tempString);
		numberOfVertices = std::stoi(tempString);
		// # OF INDICES
		std::getline(inputFile, tempString);
		numberOfIndices = std::stoi(tempString);

		verticesData.resize(numberOfVertices * 8);
		for (int i = 0; i < verticesData.size(); i++) // ORDER: p.X, p.Y, p.Z, n.X, n.Y, n.Z, U, V
		{
			std::getline(inputFile, tempString, ',');
			verticesData.at(i) = std::stof(tempString);
		}

		indices.resize(numberOfIndices);
		for (int i = 0; i < indices.size(); i++)
		{
			std::getline(inputFile, tempString, ',');
			indices.at(i) = std::stoi(tempString);
		}
		free(ptr);
	}


	unsigned int size = sizeof(MeshResource) + verticesData.size() * sizeof(float) + indices.size() * sizeof(unsigned int);
	MeshResource* meshToBeReturned = new (RM_MALLOC(size)) MeshResource(verticesData, indices, GUID);
	meshToBeReturned->setSize(size);

	/// ----------------------------------------------------
	return meshToBeReturned;
}