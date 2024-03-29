#ifndef _PB_PNG_LOADER_
#define _PB_PNG_LOADER_

#include <string>

#include "FormatLoader.h"

class PNGLoader : public FormatLoader {
public:
	PNGLoader() { m_supportedExtensions.push_back(".png"); };
	~PNGLoader() {};
	/*
	Returns a resource with the following data:
	- int height;
	- int width;
	- vector<unsigned char> image;
	'image' is structured:
	Pixel_0_R, 	Pixel_0_B,	Pixel_0_G,  Pixel_0_A, Pixel_1_R, Pixel_1_G etc.
	'image' is read row-wise:
	1------->
	2------->
	3------->
	*/
	std::string load(const std::string& path);
};

#endif //_RM_PNG_LOADER_
