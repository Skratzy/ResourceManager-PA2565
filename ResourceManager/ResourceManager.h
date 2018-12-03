#pragma once

#include <map>

#include "Resource.h"
#include "FormatLoader.h"

class ResourceManager
{
private:
	std::map<long, Resource*> m_resources;
	unsigned int m_capacity;
	unsigned int m_memUsage;

public:
	ResourceManager(unsigned int capacity = 256);
	~ResourceManager();

	Resource* load(const std::string& path);
};

