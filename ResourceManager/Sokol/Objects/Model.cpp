#include "Model.h"

#include "../../ResManAPI/Resources/MeshResource.h"
#include "../../ResManAPI/Resources/TextureResource.h"
#include "../../ResManAPI/ResourceManager.h"

Model::Model(MeshResource * mesh, TextureResource * tex)
	: m_transform(Transform())
{
	m_mesh = mesh;
	m_texture = tex;
	m_vertexCount = mesh->getVertexCount();
	m_indexCount = mesh->getIndexCount();
}

Model::~Model()
{
	ResourceManager::getInstance().decrementReference(m_mesh->getGUID());
	ResourceManager::getInstance().decrementReference(m_texture->getGUID());
}

void Model::draw(sg_draw_state& drawState, vs_params_t& vsParams)
{
	drawState.vertex_buffers[0] = m_mesh->getVertexBuffer();
	drawState.index_buffer = m_mesh->getIndexBuffer();
	drawState.fs_images[0] = m_texture->getImage();
	sg_apply_draw_state(&drawState);
	vsParams.m = m_transform.getMatrix();
	sg_apply_uniform_block(SG_SHADERSTAGE_VS, 0, &vsParams, sizeof(vsParams));
	sg_draw(0, m_indexCount, 1);
}

void Model::setMesh(MeshResource * mesh)
{
	ResourceManager::getInstance().decrementReference(m_mesh->getGUID());
	m_mesh = mesh;
}

void Model::setTexture(TextureResource * tex)
{
	ResourceManager::getInstance().decrementReference(m_texture->getGUID());
	m_texture = tex;
}

Transform & Model::getTransform()
{
	return m_transform;
}

