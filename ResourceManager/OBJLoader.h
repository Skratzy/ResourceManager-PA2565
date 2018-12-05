#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <vector>
#include <string>

#include "MyMesh.h"
#include "FormatLoader.h"

class OBJLoader : public FormatLoader
{
private:


public:
	virtual ~OBJLoader() {}

	virtual Resource* load(const std::string& path, const long GUID);
};

#endif