#ifndef MESH_RESOURCE_HPP
#define MESH_RESOURCE_HPP

#include <vector>
#include "Resource.h"

struct vertex
{
	float x, y, z;
};

struct uv
{
	float u, v;
};

class MyMesh : public Resource
{
private:

public:
	MyMesh(
		int vertexCount,
		int normalsCount,
		int texCoordsCount,
		int indexCount,
		const long GUID) : Resource(GUID)
	{
		vertices.resize(vertexCount);
		normals.resize(normalsCount);
		texCoords.resize(texCoordsCount);

		indices_v.resize(indexCount);
		indices_n.resize(indexCount);
		indices_tx.resize(indexCount);
	}

	std::vector<vertex> vertices;
	std::vector<vertex> normals; // Normals use the same struct as vertices (x, y, z)
	std::vector<uv> texCoords;

	std::vector<int> indices_v;
	std::vector<int> indices_n;
	std::vector<int> indices_tx;
};

#endif
