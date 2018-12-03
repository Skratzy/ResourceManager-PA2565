#pragma once

class Resource
{
private:
	const long m_GUID;
	unsigned int m_size;
	unsigned int m_refCount;

	

public:
	Resource(const long GUID)
		: m_GUID(GUID) {}
	virtual ~Resource() {}

	const long getGUID() const {
		return m_GUID;
	}

	unsigned int refer() {
		m_refCount++;
		return m_refCount;
	}
	unsigned int derefer() {
		m_refCount--;
		return m_refCount;
	}

};

