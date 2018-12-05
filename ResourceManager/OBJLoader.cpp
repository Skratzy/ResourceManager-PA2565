#include "Defines.h"
#include "OBJLoader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "OBJ_Loader.h"

Resource* OBJLoader::load(const std::string& path, const long GUID)
{	
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warning;
	std::string error;
	/*const char *filepath;
	const char *mtl_basedir = NULL;
	bool triangulate = true;
	bool default_vcols_fallback = true;*/

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
		std::cout << "ERROR!" << e.what();
	}

	//MyMesh* meshToBeReturned = static_cast<MyMesh*>(RM_MALLOC(sizeof(MyMesh)));
	MyMesh* meshToBeReturned = new MyMesh(attrib.vertices.size(), shapes.at(0).mesh.indices.size(), GUID);

	for (int i = 0; i < attrib.vertices.size(); i++)
	{
		meshToBeReturned->vertices.at(i).x = attrib.vertices.at(i);
	}

	return meshToBeReturned;
}

//Resource* OBJLoader::load(const std::string& path)
//{
//	MyMesh* meshToBeReturned = static_cast<MyMesh*>(RM_MALLOC(sizeof(MyMesh)));
//	objl::Loader loader;
//
//	loader.LoadFile(path);
//
//	meshToBeReturned->vertices.resize(loader.LoadedVertices.size());
//	for (int i = 0; i < loader.LoadedVertices.size(); i++)
//	{
//		meshToBeReturned->vertices.at(i).x = loader.LoadedVertices.at(i).Position.X;
//		meshToBeReturned->vertices.at(i).y = loader.LoadedVertices.at(i).Position.Y;
//		meshToBeReturned->vertices.at(i).z = loader.LoadedVertices.at(i).Position.Z;
//	}
//
//	meshToBeReturned->indices.resize(loader.LoadedIndices.size());
//	for (int i = 0; i < loader.LoadedIndices.size(); i++)
//		meshToBeReturned->indices.at(i) = loader.LoadedIndices.at(i);
//
//	return static_cast<Resource*>(meshToBeReturned);
//}