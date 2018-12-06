#ifndef _RM_RESOURCE_MANAGER_
#define _RM_RESOURCE_MANAGER_

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
	bool m_initialized;

private:


public:

	// ResourceManager Singleton functionalities
	static ResourceManager& getInstance() {
		static ResourceManager instance;
		return instance;
	}
	ResourceManager(ResourceManager const&)	 = delete;
	void operator=(ResourceManager const&)	 = delete;

	ResourceManager();
	~ResourceManager();

	void init(const unsigned int capacity);

	Resource* load(const char* path);
	void decrementReference(long key);

	void registerFormatLoader(FormatLoader* formatLoader);

	//void incrementReference(long key); SHOULDN'T BE NEEDED (done when loading already existing)
};

#endif //_RM_RESOURCE_MANAGER_