#ifndef _PT_OBJ_LOADER_HPP
#define _PT_OBJ_LOADER_HPP

#include "FormatLoader.h"


class OBJLoader : public FormatLoader
{
private:


public:
	OBJLoader() { m_supportedExtensions.push_back(".obj"); };

	~OBJLoader() {};

	our::string load(const std::string& path);
};

#endif //_PT_OBJ_LOADER_HPP