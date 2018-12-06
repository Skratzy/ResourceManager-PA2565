#include "../../Defines.h"
#include "OBJLoader.h"
#include "OBJ_Loader.h"
#include "../Resources/MeshResource.h"

Resource* OBJLoader::load(const std::string& path)
{
	MeshResource* meshToBeReturned = static_cast<MeshResource*>(RM_MALLOC(sizeof(MeshResource)));
	objl::Loader loader;

	loader.LoadFile(path);

	meshToBeReturned->vertices.resize(loader.LoadedVertices.size());
	for (unsigned int i = 0; i < loader.LoadedVertices.size(); i++)
	{
		meshToBeReturned->vertices.at(i).x = loader.LoadedVertices.at(i).Position.X;
		meshToBeReturned->vertices.at(i).y = loader.LoadedVertices.at(i).Position.Y;
		meshToBeReturned->vertices.at(i).z = loader.LoadedVertices.at(i).Position.Z;
	}

	meshToBeReturned->indices.resize(loader.LoadedIndices.size());
	for (unsigned int i = 0; i < loader.LoadedIndices.size(); i++)
		meshToBeReturned->indices.at(i) = loader.LoadedIndices.at(i);

	return meshToBeReturned;
}