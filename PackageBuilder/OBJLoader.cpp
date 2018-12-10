
#include "OBJLoader.h"
#include "OBJ_Loader.h"
#include <sstream>

our::string OBJLoader::load(const std::string& path)
{
	using namespace our;

	//MyMesh* meshToBeReturned = static_cast<MyMesh*>(malloc(sizeof(MyMesh)));
	objl::Loader loader;

	loader.LoadFile(path);

	stringstream ss;
	ss << convert(loader.LoadedVertices.size());
	ss << "\n" << convert(loader.LoadedIndices.size()) << "\n";

	string dataAsString = ss.str();
	
	for (int i = 0; i < loader.LoadedVertices.size(); i++)
	{
		ss << convert(loader.LoadedVertices.at(i).Position.X) << " "
			<< convert(loader.LoadedVertices.at(i).Position.Y) << " "
			<< convert(loader.LoadedVertices.at(i).Position.Z) << "\n";
	}
	int k = 0;
	while (k < loader.LoadedIndices.size()) {
		ss << convert(loader.LoadedIndices.at(k++)) << " ";
		ss << convert(loader.LoadedIndices.at(k++)) << " ";
		ss << convert(loader.LoadedIndices.at(k++)) << "\n";
	}

	return ss.str();
}

void OBJLoader::write(our::string & data)
{
}
