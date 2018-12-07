#ifndef _PT_FORMAT_LOADER_
#define _PT_FORMAT_LOADER_

#include <vector>
#include <string>

//#include "Resource.h"

class FormatLoader
{
protected:
	std::vector<std::string> m_supportedExtensions;

public:
	virtual ~FormatLoader() {}
	virtual std::string load(const std::string& path) = 0;

	bool extensionSupported(const std::string& extension) {
		for (auto ext : m_supportedExtensions) {
			if (ext == extension)
				return true;
		}
		return false;
	}
};

#endif //_RM_FORMAT_LOADER_