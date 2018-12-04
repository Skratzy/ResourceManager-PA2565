#include "ResourceManager.h"
#include "Defines.h"

#include <experimental/filesystem>
#include <new>


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
	Resource* res = nullptr;
	namespace fs = std::experimental::filesystem;
	long hashedPath = m_pathHasher(path);

	// Check if the resource already exists in the system
	auto it = m_resources.find(hashedPath);
	if (it != m_resources.end()) {
		// Found the resource
		res = it->second;
		res->refer();
		return res;
	}
	// Else load it
	else {
		std::string ext = fs::path(path).extension().generic_string();

		// Find the format loader corresponding to the extension
		for (auto FL : m_formatLoaders) {
			// Check if the format loader supports the extension
			if (FL->extensionSupported(ext)) {
				// Load the resource and return it
				res = FL->load(path, hashedPath);
				// Update memory usage
				m_memUsage += res->getSize();
				if (m_memUsage > m_capacity) {
					RM_DEBUG_MESSAGE("ResourceManager::load() - Memory usage exceeds the memory limit.", 0);
				}
				// Increase the reference count of the resource
				res->refer();
				// Add the loaded resource to the map
				m_resources.emplace(hashedPath, res);
				return res;
			}
		}

		RM_DEBUG_MESSAGE("ResourceManager::load() - Did not find a format loader that supported the extension '" + ext + "'", 0);
	}

	return res;
	
}

void ResourceManager::decrementReference(long key)
{
	if (m_resources.at(key)->derefer() == 0)
	{
		RM_FREE(m_resources.at(key));
		m_memUsage -= m_resources.at(key)->getSize();
		m_resources.erase(key);
	}	
}

template <typename T>
void ResourceManager::registerFormatLoader()
{
	// Allocating memory required for the format loader and initializing it using a placement new
	FormatLoader* toRegister = new (RM_MALLOC(sizeof(T))) T();
	// Put the new format loader in the vector
	m_formatLoaders.emplace_back(toRegister);
}
