#ifndef _RM_OBJ_LOADER_HPP
#define _RM_OBJ_LOADER_HPP

#include <vector>
#include <string>

#include "FormatLoader.h"

class OBJLoader : public FormatLoader
{
private:


public:
	virtual ~OBJLoader() {}

	virtual Resource* load(const std::string& path);
};

#endif //_RM_OBJ_LOADER_HPP