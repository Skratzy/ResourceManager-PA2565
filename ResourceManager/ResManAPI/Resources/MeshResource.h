#ifndef MESH_RESOURCE_HPP
#define MESH_RESOURCE_HPP

#include <vector>
#include "Resource.h"
#include "../../Defines.h"

class MeshResource : public Resource
{
private:
	sg_buffer m_vertexBuffer;
	sg_buffer m_indexBuffer;
	unsigned int m_vertexCount;
	unsigned int m_indexCount;

public:
	MeshResource(std::vector<float>& vertices, std::vector<unsigned int>& indices, const long GUID, const char* path);
	virtual ~MeshResource();

	std::vector<unsigned int> indices;

	const sg_buffer& getVertexBuffer() const;
	const sg_buffer& getIndexBuffer() const;

	const unsigned int getVertexCount() const;
	const unsigned int getIndexCount() const;
};

#endif
