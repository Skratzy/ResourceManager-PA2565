#include "Defines.h"
#include "OBJLoader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

Resource* OBJLoader::load(const std::string& path, const long GUID)
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
			path.c_str()
		);
	}
	catch(const std::exception& e)
	{
		std::cout << "ERROR: " << e.what();
	}
	/// ----------------------------------

	// STEP 2: REFORMAT THE DATA TO FIT OUR 'MyMesh' OBJECT
	/// ----------------------------------------------------
	// Calculate TOTAL number of INDICES (Shape#1-indices-count + Shape#2-indices-count + ...)
	int numberOfIndices = 0;
	for (int i = 0; i < shapes.size(); i++)
		numberOfIndices += shapes.at(i).mesh.indices.size();
	// Allocate enough space for our ENTIRE MESH
	MyMesh* meshToBeReturned = new MyMesh(
		static_cast<int>(attrib.vertices.size() / 3),
		static_cast<int>(attrib.normals.size() / 3),
		static_cast<int>(attrib.texcoords.size() / 2),
		numberOfIndices, GUID);

	int currVertex = 0; // They have a list of INDIVIDUAL COORDINATES, we have a list of VERTICES
	/// VERTICES
	for (int i = 0; i < attrib.vertices.size(); /*i++*/)
	{
		// X
		meshToBeReturned->vertices.at(currVertex).x = attrib.vertices.at(i);
		i++; // INCREMENT (for-loop)
		// Y
		meshToBeReturned->vertices.at(currVertex).y = attrib.vertices.at(i);
		i++; // INCREMENT (for-loop)
		// Z
		meshToBeReturned->vertices.at(currVertex).z = attrib.vertices.at(i);
		i++; // INCREMENT (for-loop)
		// Incrementing once; OUR OWN next vertex (1 vertex holding 3 floats)
		currVertex++; // INCREMENT (to our next vertex)
	}
	/// NORMALS
	int currNormal = 0; // They have a list of INDIVIDUAL COORDINATES, we have a list of NORMALS
	for (int i = 0; i < attrib.normals.size(); /*i++*/)
	{
		// X
		meshToBeReturned->normals.at(currNormal).x = attrib.normals.at(i);
		i++; // INCREMENT (for-loop)
		// Y
		meshToBeReturned->normals.at(currNormal).y = attrib.normals.at(i);
		i++; // INCREMENT (for-loop)
		// Z
		meshToBeReturned->normals.at(currNormal).z = attrib.normals.at(i);
		i++; // INCREMENT (for-loop)
		// Incrementing once; OUR OWN next normal (1 normal holding 3 floats)
		currNormal++; // INCREMENT (to our next normal)
	}
	/// TEXCOORDS
	int currTexCoord = 0;
	for (int i = 0; i < attrib.texcoords.size(); /*i++*/)
	{
		// U
		meshToBeReturned->texCoords.at(currTexCoord).u = attrib.texcoords.at(i);
		i++;
		// V
		meshToBeReturned->texCoords.at(currTexCoord).v = attrib.texcoords.at(i);
		i++;
		// Incrementing once; OUR OWN next uv-coordinate (1 TexCoord, 2 floats)
		currTexCoord++;
	}
	/// INDICES
	int index = 0;
	for (int i = 0; i < shapes.size(); i++)
	{
		for (int k = 0; k < shapes.at(i).mesh.indices.size(); k++)
		{
			meshToBeReturned->indices_v.at(index) = shapes.at(i).mesh.indices.at(k).vertex_index;
			meshToBeReturned->indices_n.at(index) = shapes.at(i).mesh.indices.at(k).normal_index;
			meshToBeReturned->indices_tx.at(index) = shapes.at(i).mesh.indices.at(k).texcoord_index;
			index++;
		}
	}
	/// ----------------------------------------------------
	return meshToBeReturned;
}
