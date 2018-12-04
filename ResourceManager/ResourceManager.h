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
	unsigned int m_capacity;
	unsigned int m_memUsage;
	std::hash<std::string> m_pathHasher;

private:


public:
	ResourceManager(unsigned int capacity = 256);
	~ResourceManager();

	Resource* load(const std::string& path);
	void decrementReference(long key);
	//void incrementReference(long key); SHOULDN'T BE NEEDED (done when loading already existing)
};

