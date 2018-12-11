#include "OBJReformatter.h"

#include <iostream>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

our::string OBJReformatter::load(const std::string& filePath)
{
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
		std::cout << (e.what(), 1);
	}

	if (attrib.vertices.size() < 1)
		std::cout << ("Couldn't find any vertex positions in " + std::string(filePath), 1);
	if (attrib.normals.size() < 1)
		std::cout << ("Couldn't find any vertex normals in " + std::string(filePath), 1);
	if (attrib.texcoords.size() < 1)
		std::cout << ("Couldn't find any vertex UVs in " + std::string(filePath), 1);
	/// -----------------------------------------------------------------------------------

	// STEP 2: GO THROUGH THE DATA
	/// ----------------------------------

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

			verticesData.push_back(attrib.normals[3 * index.normal_index + 0]);
			verticesData.push_back(attrib.normals[3 * index.normal_index + 1]);
			verticesData.push_back(attrib.normals[3 * index.normal_index + 2]);

			verticesData.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
			verticesData.push_back(1.f - attrib.texcoords[2 * index.texcoord_index + 1]);
		}
	}

	// STEP 3: WRITE THE DATA TO FILE INTO OUR OWN MESH FORMAT
	/// ----------------------------------
	std::string returnString = "";

	int numberOfVertices = static_cast<int>(verticesData.size() / 7);
	int numberOfIndices = static_cast<int>(indices.size());

	returnString += (numberOfVertices + "\n");
	returnString += (numberOfIndices + "\n");

	for (int i = 0; i < verticesData.size(); i++) // ORDER: p.X, p.Y, p.Z, n.X, n.Y, n.Z, U, V
	{
		returnString += verticesData.at(i);
		returnString += ",";
	}

	for (int i = 0; i < indices.size(); i++)
	{
		returnString += indices.at(i);
		returnString += ",";
	}
	/// ----------------------------------------------------
	
	auto constChars = returnString.c_str(); // get constant char* from string
	auto unsignedChars = reinterpret_cast<unsigned char*>(const_cast<char*>(constChars));

	return unsignedChars;
}