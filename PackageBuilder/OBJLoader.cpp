
#include "OBJLoader.h"
#include "OBJ_Loader.h"
#include <sstream>

std::string OBJLoader::load(const std::string& path)
{
	//MyMesh* meshToBeReturned = static_cast<MyMesh*>(malloc(sizeof(MyMesh)));
	objl::Loader loader;

	loader.LoadFile(path);

	std::stringstream ss;
	ss << loader.LoadedVertices.size();
	ss << "\n" << loader.LoadedIndices.size() << "\n";


	//std::string dataAsString = ss.str();
	
	for (int i = 0; i < loader.LoadedVertices.size(); i++)
	{
		ss << loader.LoadedVertices.at(i).Position.X << " " << loader.LoadedVertices.at(i).Position.Y << " " << loader.LoadedVertices.at(i).Position.Z << "\n";
	}
	int k = 0;
	while (k < loader.LoadedIndices.size()) {
		ss << loader.LoadedIndices.at(k++) << " ";
		ss << loader.LoadedIndices.at(k++) << " ";
		ss << loader.LoadedIndices.at(k++) << "\n";
	}
	
	return ss.str();
}