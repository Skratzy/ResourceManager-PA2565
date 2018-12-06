#include "../../Defines.h"
#include "OBJLoader.h"

Resource* OBJLoader::load(const std::string& path)
{
	MyMesh* meshToBeReturned = static_cast<MyMesh*>(RM_MALLOC(sizeof(MyMesh)));
	objl::Loader loader;

	loader.LoadFile(path);

	meshToBeReturned->vertices.resize(loader.LoadedVertices.size());
	for (int i = 0; i < loader.LoadedVertices.size(); i++)
	{
		meshToBeReturned->vertices.at(i).x = loader.LoadedVertices.at(i).Position.X;
		meshToBeReturned->vertices.at(i).y = loader.LoadedVertices.at(i).Position.Y;
		meshToBeReturned->vertices.at(i).z = loader.LoadedVertices.at(i).Position.Z;
	}

	meshToBeReturned->indices.resize(loader.LoadedIndices.size());
	for (int i = 0; i < loader.LoadedIndices.size(); i++)
		meshToBeReturned->indices.at(i) = loader.LoadedIndices.at(i);

	return static_cast<Resource*>(meshToBeReturned);
}