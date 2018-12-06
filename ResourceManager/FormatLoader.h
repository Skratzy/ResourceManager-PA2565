#ifndef _RM_FORMAT_LOADET_
#define _RM_FORMAT_LOADET_

#include <vector>
#include <string>

#include "Resource.h"

class FormatLoader
{
protected:
	std::vector<std::string> m_supportedExtensions;

public:
	virtual ~FormatLoader() {}
	virtual Resource* load(const char* path, const long GUID) = 0;

	bool extensionSupported(const std::string& extension) {
		for (auto ext : m_supportedExtensions) {
			if (ext == extension)
				return true;
		}
		return false;
	}
};

#endif //_RM_FORMAT_LOADET_