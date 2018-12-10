#include "../../Defines.h"
#include "RMMeshLoader.h"

#include "../Resources/MeshResource.h"
#include <fstream>

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

	// STEP 1: LOAD THE 'RMMesh' FILE
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

	verticesData.resize(numberOfVertices);
	for (int i = 0; i < verticesData.size(); i++) // ORDER: p.X, p.Y, p.Z, n.X, n.Y, n.Z, U, V
	{
		std::getline(inputFile, tempString, ',');
		verticesData.at(i) = std::stoi(tempString);
	}

	for (int i = 0; i < indices.size(); i++)
	{
		std::getline(inputFile, tempString, ',');
		indices.at(i) = std::stoi(tempString);
	}

	MeshResource* meshToBeReturned = new (RM_MALLOC(sizeof(MeshResource))) MeshResource(verticesData, indices, GUID);

	/// ----------------------------------------------------
	return meshToBeReturned;
}