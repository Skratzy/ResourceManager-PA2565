#pragma once

#include <map>

#include "Resource.h"
#include "FormatLoader.h"

class ResourceManager
{
private:
	std::map<long, Resource*> m_resources;
	unsigned int memUsage;

public:
	ResourceManager();
	~ResourceManager();

	Resource* load(const std::string& path);
	void decrementReference(long key);
	//void incrementReference(long key); SHOULDN'T BE NEEDED (done when loading already existing)
};

