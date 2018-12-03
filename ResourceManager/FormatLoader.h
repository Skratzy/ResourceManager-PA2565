#pragma once

#include <vector>
#include <string>

#include "Resource.h"

class FormatLoader
{
private:
	std::vector<std::string> supportedExtensions;

public:
	FormatLoader();
	~FormatLoader();

	virtual Resource* load(const std::string& path);


};

