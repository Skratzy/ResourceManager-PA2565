#ifndef _RM_RESOURCE_
#define _RM_RESOURCE_

class Resource
{
private:
	const long m_GUID;
	const char* m_path;
	unsigned int m_refCount;
	unsigned int m_size;	// Initialize at inheritors constructor!

public:
	Resource(const long GUID, const char* path)
		: m_GUID(GUID), m_path(path) {
		m_size = 0;
		m_refCount = 0;
	}
	virtual ~Resource() {}

	const long getGUID() const {
		return m_GUID;
	}

	const char* getPath() const {
		return m_path;
	}

	unsigned int refer() {
		m_refCount++;
		return m_refCount;
	}
	unsigned int derefer() {
		m_refCount--;
		return m_refCount;
	}

	void setSize(int size) {
		this->m_size = size;
	}
	const unsigned int getSize() const {
		return m_size;
	}


};

#endif //_RM_RESOURCE_