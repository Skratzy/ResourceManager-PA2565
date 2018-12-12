#include <experimental/filesystem>
#include <new>

#include "ResourceManager.h"
#include "../Defines.h"
#include "Resources/Resource.h"
#include "FormatLoaders/FormatLoader.h"


void ResourceManager::asyncLoadStart()
{
	while (m_running) {
		std::unique_lock<std::mutex> lock(m_asyncMutex);
		m_cond.wait(lock);

		// Critical region
		if (m_asyncResJobs.size() > 0) {
			auto currJob = m_asyncResJobs.begin();
			Resource* res = load(currJob->second.filepath);
			for (auto callback : currJob->second.callbacks)
				callback(res);
			m_asyncResJobs.erase(currJob);
		}
	}
}

ResourceManager::ResourceManager()
{
	m_capacity = 0;
	m_memUsage = 0;
	m_initialized = false;
	m_running = true;

	// Start the async loading thread
	m_asyncLoadThread = std::thread(std::bind(&ResourceManager::asyncLoadStart, this));
}


ResourceManager::~ResourceManager()
{
	m_running = false;
	m_cond.notify_all();
	for (auto FL : m_formatLoaders)
		RM_DELETE(FL);
	for (auto RES : m_resources)
		RM_DELETE(RES.second);
	m_asyncLoadThread.join();
}


void ResourceManager::init(const unsigned int capacity) {
	if (!m_initialized) {
		m_capacity = capacity;
		m_initialized = true;
	}
}


Resource * ResourceManager::load(const char* path)
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
		// Only one thread can create and load new resources to the resource manager

		std::lock_guard<std::mutex> lock(m_mutex);

		// Additional check if several threads tries to load the same asset it does
		// not create the same resource more than once.
		auto it = m_resources.find(hashedPath);
		if (it != m_resources.end()) {
			// Found the resource
			res = it->second;
			res->refer();
			return res;
		}
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
					RM_DEBUG_MESSAGE(("ResourceManager::load() - Memory usage exceeds the memory limit. (" + std::to_string(m_memUsage / (1024)) + "KB / " + std::to_string(m_capacity / (1024)) + "KB) (Usage / Capacity)"), 0);
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

Resource* ResourceManager::asyncLoad(const char * path, std::function<void(Resource*)> callback)
{
	long hashedPath = m_pathHasher(path);
	Resource* res = nullptr;

	// Check if the resource already exists in the system
	auto it = m_resources.find(hashedPath);
	if (it != m_resources.end()) {
		// Found the resource
		res = it->second;
		res->refer();
		callback(res);
		return;
	}
	else {
		// Critical region
		std::lock_guard<std::mutex> lock(m_asyncMutex);

		// Check if the resource already exists in the system
		it = m_resources.find(hashedPath);
		if (it != m_resources.end()) {
			// Found the resource
			res = it->second;
			res->refer();
			callback(res);
			return;
		}
		
		// Find out if the job is already queued
		auto asyncJobsIt = m_asyncResJobs.find(hashedPath);
		// The job already exists, push back another callback
		if (asyncJobsIt != m_asyncResJobs.end()) {
			asyncJobsIt->second.callbacks.push_back(callback);
		}
		else {
			std::vector<std::function<void(Resource*)>> callbacks;
			callbacks.push_back(callback);
			m_asyncResJobs.emplace(hashedPath, AsyncJob{ path, callbacks });
			m_cond.notify_one();
		}

		return nullptr;
	}
}

void ResourceManager::decrementReference(long key)
{
	if (m_resources.at(key)->derefer() == 0)
	{
		m_memUsage -= m_resources.at(key)->getSize();
		m_resources.at(key)->~Resource();
		RM_FREE(m_resources.at(key));
		m_resources.erase(key);
	}	
}

void ResourceManager::registerFormatLoader(FormatLoader* formatLoader)
{
	// Put the new format loader in the vector
	m_formatLoaders.emplace_back(formatLoader);
}
