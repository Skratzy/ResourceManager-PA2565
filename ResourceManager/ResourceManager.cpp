#include "ResourceManager.h"



ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

Resource * ResourceManager::load(const std::string & path)
{
	return nullptr;
}

void ResourceManager::decrementReference(long key)
{
	if (m_resources.at(key)->derefer() == 0)
	{
		delete m_resources.at(key);
		m_resources.erase(key);
	}
}
