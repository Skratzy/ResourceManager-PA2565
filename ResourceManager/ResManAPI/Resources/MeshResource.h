#ifndef MESH_RESOURCE_HPP
#define MESH_RESOURCE_HPP

#include <vector>
#include "Resource.h"
#include "../../Defines.h"

struct vertex
{
	float x, y, z;
};

struct uv
{
	float u, v;
};

class MeshResource : public Resource
{
private:
	sg_buffer m_vertexBuffer;
	sg_buffer m_indexBuffer;
	bool m_isIndexed;
	unsigned int m_vertexCount;
	unsigned int m_indexCount;

public:
	MeshResource(
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
	const sg_buffer& getVertexBuffer() const;
	const sg_buffer& getIndexBuffer() const;
	const bool getIsIndexed() const;
	const unsigned int getVertexCount();
	const unsigned int getIndexCount();
};

#endif
