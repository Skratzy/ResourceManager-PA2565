#include "ResourceManager.h"



ResourceManager::ResourceManager(unsigned int capacity)
{
	m_capacity = capacity;
	m_memUsage = 0;
}


ResourceManager::~ResourceManager()
{
}

Resource * ResourceManager::load(const std::string & path)
{
	// Update memory usage
	//m_memUsage += formatLoaders.load(path);
	return nullptr;
}
