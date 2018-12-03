#pragma once

class Resource
{
private:
	long m_GUID;
	void* m_data;
	unsigned int m_size;
	unsigned int m_refCount;

	

public:
	Resource();
	~Resource();

	const long getGUID() const;
	void* getData() const;

	void refer();
	void derefer();

};

