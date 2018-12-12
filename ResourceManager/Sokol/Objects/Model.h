#ifndef _RM_MODEL_
#define _RM_MODEL_

#include <vector>

#include "../../Defines.h"
#include "Transform.hpp"

class MeshResource;
class TextureResource;

class Model {
private:
	MeshResource* m_mesh;
	TextureResource* m_texture;
	Transform m_transform;
	unsigned int m_vertexCount;
	unsigned int m_indexCount;

public:
	Model(MeshResource * mesh, TextureResource * tex);
	~Model();

	void draw(sg_draw_state& drawState, vs_params_t& vsParams);

	void setMesh(MeshResource* mesh);
	void setTexture(TextureResource* tex);

	Transform& getTransform();

};

#endif //_RM_MODEL_