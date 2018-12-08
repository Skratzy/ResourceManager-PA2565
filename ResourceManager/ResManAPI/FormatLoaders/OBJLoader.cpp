#include "../../Defines.h"
#include "OBJLoader.h"
#include "OBJ_Loader.h"
#include "../Resources/MeshResource.h"

OBJLoader::OBJLoader()
{
	m_supportedExtensions.push_back(".obj");
}

Resource* OBJLoader::load(const char* path, const long GUID)
{
	objl::Loader loader;

	loader.LoadFile(path);

	/*meshToBeReturned->vertices.resize(loader.LoadedVertices.size() * 3);
	for (unsigned int i = 0; i < loader.LoadedVertices.size(); i++)
	{
		meshToBeReturned->vertices.at(i).x = loader.LoadedVertices.at(i).Position.X;
		meshToBeReturned->vertices.at(i).y = loader.LoadedVertices.at(i).Position.Y;
		meshToBeReturned->vertices.at(i).z = loader.LoadedVertices.at(i).Position.Z;
	}

	meshToBeReturned->indices.resize(loader.LoadedIndices.size());
	for (unsigned int i = 0; i < loader.LoadedIndices.size(); i++)
		meshToBeReturned->indices.at(i) = loader.LoadedIndices.at(i);*/

	std::vector<float> vertices(loader.LoadedVertices.size() * 3);
	for (unsigned int i = 0; i < loader.LoadedVertices.size(); i++)
	{
		int index = i * 3;
		vertices.at(index) = loader.LoadedVertices.at(i).Position.X;
		vertices.at(index + 1) = loader.LoadedVertices.at(i).Position.Y;
		vertices.at(index + 2) = loader.LoadedVertices.at(i).Position.Z;
	}
	std::vector<unsigned int> indices(loader.LoadedVertices.size());
	for (unsigned int i = 0; i < loader.LoadedIndices.size(); i++)
		indices.at(i) = loader.LoadedIndices.at(i);

	MeshResource* meshToBeReturned = static_cast<MeshResource*>( new (RM_MALLOC(sizeof(MeshResource))) MeshResource(vertices, indices, GUID) );


	return meshToBeReturned;
}