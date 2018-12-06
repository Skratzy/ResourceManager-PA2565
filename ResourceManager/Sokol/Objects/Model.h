#ifndef _RM_MODEL_
#define _RM_MODEL_

#include <vector>

#include "../../ResManAPI/Resources/MeshResource.h"
#include "../../ResManAPI/Resources/TextureResource.h"

class Model {
private:
	MeshResource* m_mesh;
	TextureResource* m_texture;

public:
	Model(MeshResource* mesh, TextureResource* tex);
	~Model();



};

#endif //_RM_MODEL_