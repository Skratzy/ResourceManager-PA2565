#ifndef MY_MESH_HPP
#define MY_MESH_HPP

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

#endif