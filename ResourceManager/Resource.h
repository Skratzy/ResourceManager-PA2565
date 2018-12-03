#pragma once

class Resource
{
private:
	const long m_GUID;
	unsigned int m_refCount;
	unsigned int m_size;	// Initialize at inheritors constructor!

public:
	Resource(const long GUID)
		: m_GUID(GUID) {
		this->m_refCount = 1;
	}
	virtual ~Resource() {}

	const long getGUID() const {
		return m_GUID;
	}

	void refer() {
		m_refCount++;
	}
	void derefer() {
		m_refCount--;
	}

	void setSize(int size) {
		this->m_size = size;
	}
	const unsigned int getSize() const {
		return m_size;
	}


};

