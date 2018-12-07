#ifndef _PT_OBJ_LOADER_HPP
#define _PT_OBJ_LOADER_HPP

#include "FormatLoader.h"


class OBJLoader : public FormatLoader
{
private:


public:
	virtual ~OBJLoader() {}

	virtual Resource* load(const std::string& path);
};

#endif //_PT_OBJ_LOADER_HPP