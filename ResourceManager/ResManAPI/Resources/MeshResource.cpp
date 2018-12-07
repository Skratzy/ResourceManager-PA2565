#include "MeshResource.h"

MeshResource::MeshResource(std::vector<float>& vertices, std::vector<float>& indices, const long GUID)
	: Resource(GUID)
{
	m_isIndexed = false;

	m_vertexCount = vertices.size();
	// Build vertex buffer
	sg_buffer_desc sgVbd{ 0 };
	sgVbd.type = SG_BUFFERTYPE_VERTEXBUFFER;
	sgVbd.size = m_vertexCount;
	sgVbd.content = vertices.data();
	m_vertexBuffer = sg_make_buffer(&sgVbd);


	m_indexCount = indices.size();
	// Check if the mesh has indices
	if (m_indexCount > 0) {
		m_isIndexed = true;

		// Build index buffer
		sg_buffer_desc sgIbd{ 0 };
		sgIbd.type = SG_BUFFERTYPE_INDEXBUFFER;
		sgIbd.size = m_indexCount;
		sgIbd.content = indices.data();
		m_indexBuffer = sg_make_buffer(&sgIbd);
	}
}

MeshResource::~MeshResource()
{
}

const sg_buffer & MeshResource::getVertexBuffer() const
{
	return m_vertexBuffer;
}

const sg_buffer & MeshResource::getIndexBuffer() const
{
	return m_indexBuffer;
}

const bool MeshResource::getIsIndexed() const
{
	return m_isIndexed;
}

const unsigned int MeshResource::getVertexCount()
{
	return m_vertexCount;
}

const unsigned int MeshResource::getIndexCount()
{
	return m_indexCount;
}
