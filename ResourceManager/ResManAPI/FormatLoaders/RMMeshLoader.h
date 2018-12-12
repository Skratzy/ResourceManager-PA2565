#ifndef RMMESH_LOADER_HPP
#define RMMESH_LOADER_HPP

#include <vector>
#include <string>

#include "FormatLoader.h"

class RMMeshLoader : public FormatLoader
{
private:


public:
	RMMeshLoader() { m_supportedExtensions.push_back(".rmmesh"); }
	virtual ~RMMeshLoader() {}

	virtual Resource* load(const char* path, const long GUID);
};

#endif