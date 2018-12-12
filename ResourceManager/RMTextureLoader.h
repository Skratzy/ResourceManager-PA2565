#ifndef _RM_TEXTURE_LOADER_H
#define _RM_TEXTURE_LOADER_H

#include "ResManAPI/FormatLoaders/FormatLoader.h"

class RMTextureLoader : public FormatLoader {
private:
public:
	RMTextureLoader();
	~RMTextureLoader();

	virtual Resource* load(const char* path, const long GUID);
};



#endif
