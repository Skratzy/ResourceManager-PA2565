#ifndef _RM_RESOURCE_MANAGER_
#define _RM_RESOURCE_MANAGER_

#include <map> // Map
#include <vector> // Vector
#include <functional> // Hash
#include <string> // String
#include <mutex>
#include <functional>
#include <thread>
#include <condition_variable>
#include <queue>

class Resource;
class FormatLoader;

class ResourceManager
{
private:
	std::map<long, Resource*> m_resources;
	
	std::vector<FormatLoader*> m_formatLoaders;
	
	unsigned int m_capacity;
	unsigned int m_memUsage;
	
	std::mutex m_mutex;
	
	std::hash<std::string> m_pathHasher;
	
	bool m_initialized;

	struct AsyncJob {
		const char* filepath;
		std::vector<std::function<void(Resource*)>> callbacks;
	};
	std::queue<long> m_asyncJobQueue;
	std::map<long, AsyncJob> m_asyncResJobs;
	std::thread m_asyncLoadThread;
	std::condition_variable m_cond;
	std::mutex m_asyncMutex;
	std::mutex m_asyncLoadMutex;
	bool m_running;


private:
	void asyncLoadStart();

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
	void cleanup();

	void init(const unsigned int capacity);

	Resource* load(const char* path);
	void asyncLoad(const char* path, std::function<void(Resource*)> callback);

	void decrementReference(long key);

	void registerFormatLoader(FormatLoader* formatLoader);

};

#endif //_RM_RESOURCE_MANAGER_