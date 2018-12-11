#ifndef OBJ_REFORMATTER_HPP
#define OBJ_REFORMATTER_HPP

#include <vector>
#include <string>

#include <iostream>

#include "FormatLoader.h"

class OBJReformatter : public FormatLoader
{
private:


public:
	OBJReformatter() { m_supportedExtensions.push_back(".obj"); };
	~OBJReformatter() {};

	our::string load(const std::string& filePath);
	void write(our::string &data) { std::cout << "WRITING!"; };
};

#endif
