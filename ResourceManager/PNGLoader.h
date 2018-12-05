#ifndef _RM_PNG_LOADER_
#define _RM_PNG_LOADER_

#include <string>

#include "FormatLoader.h"
#include "Resource.h"

class ResourcePNG : public Resource {
public:
	unsigned int m_width;
	unsigned int m_height;
	std::vector<unsigned char> m_image;
	// Constructor is used to attach image to 
	ResourcePNG(int width, int height, std::vector<unsigned char> image, const long GUID) : Resource(GUID) {
		this->m_width = width;
		this->m_height = height;
		this->m_image = image;
		this->setSize(sizeof(unsigned char) * 4 * width * height);
	}
	~ResourcePNG() {};
};

class PNGLoader : public FormatLoader {
public:
	PNGLoader() {};
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
	Resource* load(const std::string& path, const long GUID);
};

#endif //_RM_PNG_LOADER_
