#include "../../Defines.h"
#include "OBJLoader.h"
#include "OBJ_Loader.h"
#include "../Resources/MeshResource.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <experimental/filesystem>
#include <map>
#include <unordered_map>

Resource* OBJLoader::load(const char* path, const long GUID)
{	
	// Checking if the asset is in a package
	std::string filePath = path;
	size_t check = 0;
	check = filePath.find(".zip");
	bool loadZipped = false;
	if (check < filePath.length()) {
		loadZipped = true;
		filePath = extractFile(path, check);
	}

	// OBJ_Loader Library Variables
	/// ----------------------------------------
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warning;
	std::string error;
	/// ----------------------------------------

	// STEP 1: LOAD THE OBJ FILE
	/// ----------------------------------
	try
	{
		tinyobj::LoadObj(
			&attrib,
			&shapes,
			&materials,
			&warning,
			&error,
			filePath.c_str()
		);
	}
	catch (const std::exception& e)
	{
		RM_DEBUG_MESSAGE(e.what(), 1);
	}

	if (attrib.vertices.size() < 1)
		RM_DEBUG_MESSAGE("Couldn't find any vertex positions in " + std::string(path), 1);
	if (attrib.normals.size() < 1)
		RM_DEBUG_MESSAGE("Couldn't find any vertex normals in " + std::string(path), 0);
	if (attrib.texcoords.size() < 1)
		RM_DEBUG_MESSAGE("Couldn't find any vertex UVs in " + std::string(path), 0);

	std::vector<uint32_t> indices;
	std::vector<float> verticesData;
	// Very inefficient way of drawing loading the meshes
	for (const auto& shape : shapes) // PER SHAPE
	{
		for (const auto& index : shape.mesh.indices) // PER INDEX (per shape)
		{
			// Vertex Index
			indices.push_back(indices.size());
			
			verticesData.push_back(attrib.vertices[3 * index.vertex_index + 0]);
			verticesData.push_back(attrib.vertices[3 * index.vertex_index + 1]);
			verticesData.push_back(attrib.vertices[3 * index.vertex_index + 2]);
			
			// Check if there's normals data in file, else use faux data (Should calculate normals)
			if (attrib.normals.size() > 0) {
				verticesData.push_back(attrib.normals[3 * index.normal_index + 0]);
				verticesData.push_back(attrib.normals[3 * index.normal_index + 1]);
				verticesData.push_back(attrib.normals[3 * index.normal_index + 2]);
			}
			else {
				verticesData.push_back(1.f);
				verticesData.push_back(1.f);
				verticesData.push_back(0.f);
			}

			// Check if there's texCoord data in file, else use faux data
			if (attrib.texcoords.size() > 0) {
				verticesData.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
				verticesData.push_back(1.f - attrib.texcoords[2 * index.texcoord_index + 1]);
			}
			else {
				verticesData.push_back(0.f);
				verticesData.push_back(0.f);				
			}
		}
	}

	unsigned int size = sizeof(MeshResource) + verticesData.size() * sizeof(float) + indices.size() * sizeof(unsigned int);
	MeshResource* meshToBeReturned = new (RM_MALLOC(size)) MeshResource(verticesData, indices, GUID);
	meshToBeReturned->setSize(size);
	/// ----------------------------------------------------

	if (loadZipped) {
		// Deleting extracted file once loaded in to memory
		std::experimental::filesystem::remove(filePath.c_str());
	}

	return meshToBeReturned;
}
