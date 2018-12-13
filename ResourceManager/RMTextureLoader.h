#ifndef _RM_TEXTURE_LOADER_H
#define _RM_TEXTURE_LOADER_H

#include "ResManAPI/FormatLoaders/FormatLoader.h"

class Resource;

class RMTextureLoader : public FormatLoader {
private:
public:
	RMTextureLoader();
	~RMTextureLoader();

	Resource* load(const char* path, const long GUID);
};



#endif
