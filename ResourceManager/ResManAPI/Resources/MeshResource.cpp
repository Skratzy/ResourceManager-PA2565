#include "MeshResource.h"

MeshResource::MeshResource(std::vector<float>& vertices, std::vector<unsigned int>& indices, const long GUID)
	: Resource(GUID)
{
	// Build vertex buffer
	sg_buffer_desc sgVbd{ 0 };
	sgVbd.type = SG_BUFFERTYPE_VERTEXBUFFER;
	m_vertexCount = vertices.size();
	sgVbd.size = m_vertexCount * sizeof(float);
	sgVbd.content = vertices.data();
	m_vertexBuffer = sg_make_buffer(&sgVbd);


	// Build index buffer
	sg_buffer_desc sgIbd{ 0 };
	sgIbd.type = SG_BUFFERTYPE_INDEXBUFFER;
	m_indexCount = indices.size();
	sgIbd.size = m_indexCount * sizeof(unsigned int);
	sgIbd.content = indices.data();
	m_indexBuffer = sg_make_buffer(&sgIbd);
}

MeshResource::~MeshResource()
{
	sg_destroy_buffer(m_vertexBuffer);
	sg_destroy_buffer(m_indexBuffer);
}

const sg_buffer & MeshResource::getVertexBuffer() const
{
	return m_vertexBuffer;
}

const sg_buffer & MeshResource::getIndexBuffer() const
{
	return m_indexBuffer;
}

const unsigned int MeshResource::getVertexCount() const
{
	return m_vertexCount;
}

const unsigned int MeshResource::getIndexCount() const
{
	return m_indexCount;
}
