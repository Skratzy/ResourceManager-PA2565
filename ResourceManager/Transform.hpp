#ifndef _TRANSFORM_
#define _TRANSFORM_

#include "Defines.h"

class Transform
{
private:
	hmm_mat4 m_transformMatrix;

	hmm_vec3 m_translation;
	hmm_vec3 m_rotation;
	hmm_vec3 m_scale;

	bool m_matUpdated;

public:
	Transform();
	~Transform();

	void translate(hmm_vec3 translation);
	void rotateAroundX(float angle);
	void rotateAroundY(float angle);
	void rotateAroundZ(float angle);
	void setScale(hmm_vec3 scale);
	
	hmm_vec3 getTranslation();
	hmm_vec3 getRotation();
	hmm_vec3 getScale();
	hmm_mat4 getMatrix();
};

#endif //_TRANSFORM_