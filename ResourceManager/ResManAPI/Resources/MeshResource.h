#ifndef _RM_MESH_RESOURCE_HPP_
#define _RM_MESH_RESOURCE_HPP_

#include <vector>

#include "Resource.h"
#include "../../Defines.h"

class MeshResource : public Resource
{
private:
	sg_buffer m_vertexBuffer;
	sg_buffer m_indexBuffer;
	bool m_isIndexed;
	unsigned int m_vertexCount;
	unsigned int m_indexCount;

public:
	MeshResource(std::vector<float>& vertices, std::vector<float>& indices, const long GUID);
	virtual ~MeshResource();

	const sg_buffer& getVertexBuffer() const;
	const sg_buffer& getIndexBuffer() const;
	const bool getIsIndexed() const;
	const unsigned int getVertexCount();
	const unsigned int getIndexCount();
};

#endif //_RM_MESH_RESOURCE_HPP_