#include "ResourceManager.h"

#include <experimental/filesystem>


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
					/*
						OBS!!!
						CONVERT FILEPATH TO GUID BELOW
					*/
				const long GUID_derived_from_filepath = 0;
				res = FL->load(path, GUID_derived_from_filepath);
				// Update memory usage
				m_memUsage += res->getSize();
				res->refer();
				// Add the loaded resource to the map
				m_resources.emplace(hashedPath, res);
				return res;
			}
		}

		throw std::exception(("Did not find a format loader that supported the extension '" + ext + "'").c_str());
	}

	return res;
}
