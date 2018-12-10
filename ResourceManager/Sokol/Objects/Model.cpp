#include "Model.h"

#include "../../ResManAPI/Resources/MeshResource.h"
#include "../../ResManAPI/Resources/TextureResource.h"

Model::Model(MeshResource * mesh, TextureResource * tex, sg_pipeline& pipeline)
	: m_drawState {0}
	, m_transform(Transform())
{
	m_drawState.pipeline = pipeline;
	m_drawState.vertex_buffers[0] = mesh->getVertexBuffer();
	m_drawState.index_buffer = mesh->getIndexBuffer();
	m_drawState.fs_images[0] = tex->getImage();
	m_vertexCount = mesh->getVertexCount();
	m_indexCount = mesh->getIndexCount();
}

Model::~Model()
{
}

void Model::draw(vs_params_t& vsParams)
{
	sg_apply_draw_state(&m_drawState);
	vsParams.m = m_transform.getMatrix();
	sg_apply_uniform_block(SG_SHADERSTAGE_VS, 0, &vsParams, sizeof(vsParams));
	sg_draw(0, m_indexCount, 1);
}

Transform & Model::getTransform()
{
	return m_transform;
}
