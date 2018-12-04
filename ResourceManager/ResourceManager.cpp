#include "ResourceManager.h"
#include "Defines.h"



ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

Resource * ResourceManager::load(const std::string & path)
{
	
}

void ResourceManager::decrementReference(long key)
{
	if (m_resources.at(key)->derefer() == 0)
	{
		RM_FREE(m_resources.at(key));
		m_resources.erase(key);
	}	
}
