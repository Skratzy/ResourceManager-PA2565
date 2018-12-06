#ifndef _RM_MESH_RESOURCE_HPP_
#define _RM_MESH_RESOURCE_HPP_

#include <vector>

#include "Resource.h"

struct vertex
{
	float x, y, z;
};

class MeshResource : public Resource
{
private:

public:
	MeshResource();
	virtual ~MeshResource();

	std::vector<vertex> vertices;
	std::vector<int> indices;
};

#endif //_RM_MESH_RESOURCE_HPP_