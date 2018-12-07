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
	sg_draw_state m_drawState;
	Transform m_transform;
	unsigned int m_vertexCount;
	unsigned int m_indexCount;

public:
	Model(MeshResource * mesh, TextureResource * tex, sg_pipeline& pipeline);
	~Model();

	void draw(vs_params_t vsParams);

	Transform& getTransform();

};

#endif //_RM_MODEL_