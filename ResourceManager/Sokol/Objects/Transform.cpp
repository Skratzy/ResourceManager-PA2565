#include "Transform.hpp"

Transform::Transform()
{
	m_scale = HMM_Vec3(1.f, 1.f, 1.f);
	m_translation = HMM_Vec3(0.f, 0.f, 0.f);
	m_rotation = HMM_Vec3(0.f, 0.f, 0.f);
	// Construct with an identity matrix
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_transformMatrix.Elements[i][j] = (i == j) ? 1.f : 0.f;
		}
	}
	m_matUpdated = true;
}

Transform::~Transform()
{
}

void Transform::translate(hmm_vec3 translation)
{
	m_matUpdated = true;
	m_translation = HMM_AddVec3(m_translation,translation);
}

void Transform::rotateAroundX(float angle)
{
	m_matUpdated = true;
	m_rotation.X += angle;
}

void Transform::rotateAroundY(float angle)
{
	m_matUpdated = true;
	m_rotation.Y += angle;
}

void Transform::rotateAroundZ(float angle)
{
	m_matUpdated = true;
	m_rotation.Z += angle;
}

void Transform::setScale(hmm_vec3 scale)
{
	m_matUpdated = true;
	m_scale = scale;
}

hmm_vec3 Transform::getTranslation()
{
	return m_translation;
}

hmm_vec3 Transform::getRotation()
{
	return m_rotation;
}

hmm_vec3 Transform::getScale()
{
	return m_scale;
}

hmm_mat4 Transform::getMatrix()
{
	if (m_matUpdated) {
		m_transformMatrix = HMM_Scale(m_scale);
		m_transformMatrix = HMM_MultiplyMat4(HMM_Rotate(m_rotation.X, HMM_Vec3(1.f, 0.f, 0.f)), m_transformMatrix);
		m_transformMatrix = HMM_MultiplyMat4(HMM_Rotate(m_rotation.Y, HMM_Vec3(0.f, 1.f, 0.f)), m_transformMatrix);
		m_transformMatrix = HMM_MultiplyMat4(HMM_Rotate(m_rotation.Z, HMM_Vec3(0.f, 0.f, 1.f)), m_transformMatrix);
		m_transformMatrix = HMM_MultiplyMat4(HMM_Translate(m_translation), m_transformMatrix);

		m_matUpdated = false;
	}

	return m_transformMatrix;
}
