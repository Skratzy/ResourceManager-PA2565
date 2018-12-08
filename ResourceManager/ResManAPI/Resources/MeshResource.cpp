#include "MeshResource.h"

MeshResource::MeshResource(std::vector<float>& vertices, std::vector<unsigned int>& indices, const long GUID)
	: Resource(GUID)
{
	/* cube vertex buffer */
    /*float verticess[] = {
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f
    };
	
	sg_buffer_desc sgVbd{ 0 };
	sgVbd.type = SG_BUFFERTYPE_VERTEXBUFFER;
	m_vertexCount = sizeof(verticess);
	sgVbd.size = m_vertexCount;
	m_vertexCount /= sizeof(float);
	sgVbd.content = verticess;
	m_vertexBuffer = sg_make_buffer(&sgVbd);*/

	/* create an index buffer for the cube */
	/*uint16_t indicess[] = {
		0, 1, 2,  0, 2, 3,
		6, 5, 4,  7, 6, 4,
		8, 9, 10,  8, 10, 11,
		14, 13, 12,  15, 14, 12,
		16, 17, 18,  16, 18, 19,
		22, 21, 20,  23, 22, 20
	};

	sg_buffer_desc sgIbd{ 0 };
	sgIbd.type = SG_BUFFERTYPE_INDEXBUFFER;
	m_indexCount = sizeof(indicess);
	sgIbd.size = m_indexCount;
	m_indexCount /= sizeof(uint16_t);
	sgIbd.content = indicess;
	m_indexBuffer = sg_make_buffer(&sgIbd);*/
	
	m_isIndexed = false;

	// Build vertex buffer
	sg_buffer_desc sgVbd{ 0 };
	sgVbd.type = SG_BUFFERTYPE_VERTEXBUFFER;
	m_vertexCount = vertices.size();
	sgVbd.size = m_vertexCount * sizeof(float);
	sgVbd.content = vertices.data();
	m_vertexBuffer = sg_make_buffer(&sgVbd);


	m_indexCount = indices.size();
	// Check if the mesh has indices
	if (m_indexCount > 0) {
		m_isIndexed = true;

		// Build index buffer
		sg_buffer_desc sgIbd{ 0 };
		sgIbd.type = SG_BUFFERTYPE_INDEXBUFFER;
		m_indexCount = indices.size();
		sgIbd.size = m_indexCount * sizeof(unsigned int);
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
