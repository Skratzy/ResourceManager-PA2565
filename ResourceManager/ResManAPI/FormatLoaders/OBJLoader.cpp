#include "../../Defines.h"
#include "OBJLoader.h"
#include "OBJ_Loader.h"
#include "../Resources/MeshResource.h"

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
	MeshResource* meshToBeReturned = new MeshResource(
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
		i++; // INCREMENT (for-loop)
		// V
		meshToBeReturned->texCoords.at(currTexCoord).v = attrib.texcoords.at(i);
		i++; // INCREMENT (for-loop)
		// Incrementing once; OUR OWN next uv-coordinate (1 TexCoord, 2 floats)
		currTexCoord++; // INCREMENT (to our next texCoord)
	}
	/// INDICES
	int index = 0;
	for (int i = 0; i < shapes.size(); i++) // PER SHAPE
	{
		for (int k = 0; k < shapes.at(i).mesh.indices.size(); k++) // PER INDEX (per shape)
		{
			// Vertex Index
			meshToBeReturned->indices_v.at(index) = shapes.at(i).mesh.indices.at(k).vertex_index;
			// Normal Index
			meshToBeReturned->indices_n.at(index) = shapes.at(i).mesh.indices.at(k).normal_index;
			// TexCoord Index
			meshToBeReturned->indices_tx.at(index) = shapes.at(i).mesh.indices.at(k).texcoord_index;
			index++; // INCREMEMENT (to our next set of indices)
		}
	}
	std::vector<unsigned int> indices(loader.LoadedVertices.size());
	for (unsigned int i = 0; i < loader.LoadedIndices.size(); i++)
		indices.at(i) = loader.LoadedIndices.at(i);

	MeshResource* meshToBeReturned = static_cast<MeshResource*>( new (RM_MALLOC(sizeof(MeshResource))) MeshResource(vertices, indices, GUID) );


	/// ----------------------------------------------------
	return meshToBeReturned;
}
