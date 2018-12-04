#ifndef OBJ_LOADER_HPP
#define OBJ_LOADER_HPP

#include <vector>
#include <string>

#include "MyMesh.h"
#include "FormatLoader.h"
#include "OBJ_Loader.h"

class OBJLoader : public FormatLoader
{
private:


public:
	virtual ~OBJLoader() {}

	virtual Resource* load(const std::string& path);
};

#endif