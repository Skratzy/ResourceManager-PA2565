#ifndef MY_MESH_HPP
#define MY_MESH_HPP

#include <vector>
#include "Resource.h"

struct vertex
{
	float x, y, z;
};

class MyMesh : public Resource
{
private:

public:
	MyMesh(int verticesCount, int indicesCount, const long GUID) : Resource(GUID)
	{
		vertices.resize(verticesCount);
		indices.resize(indicesCount);
	}

	std::vector<vertex> vertices;
	std::vector<int> indices;
};

#endif