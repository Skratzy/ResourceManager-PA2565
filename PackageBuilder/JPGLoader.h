#ifndef _PB_JPG_LOADER_H
#define _PB_JPG_LOADER_H

#include "FormatLoader.h"

class Resource;

class JPGLoader : public FormatLoader {
public:
	JPGLoader() {
		this->m_supportedExtensions.push_back(".jpg");
	}
	~JPGLoader() {}
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
	our::string load(const std::string& path);
};

#endif