#ifndef _RM_MY_MESH_HPP_
#define _RM_MY_MESH_HPP_

#include <vector>

#include "Resource.h"

struct vertex
{
	float x, y, z;
};

class MyMesh : public Resource
{
private:

public:
	MyMesh();
	virtual ~MyMesh();

	std::vector<vertex> vertices;
	std::vector<int> indices;
};

#endif //_RM_MY_MESH_HPP_