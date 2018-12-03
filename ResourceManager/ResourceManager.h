#pragma once

#include <map> // Map
#include <vector> // Vector
#include <functional> // Hash
#include <string> // String

#include "Resource.h"
#include "FormatLoader.h"

class ResourceManager
{
private:
	std::map<long, Resource*> m_resources;
	std::vector<FormatLoader*> m_formatLoaders;
	unsigned int memUsage;
	std::hash<std::string> m_pathHasher;

private:


public:
	ResourceManager();
	~ResourceManager();

	Resource* load(const std::string& path);
};

