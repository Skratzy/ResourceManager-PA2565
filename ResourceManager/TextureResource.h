#pragma once
//#ifndef _RM_TEXTURERESOURCE_H
//#define _RM_TEXTURERESOURCE_H

#include "Resource.h"
#include <vector>

class TextureResource : public Resource {
public:
	unsigned int m_width;
	unsigned int m_height;
	std::vector<unsigned char> m_image;
	// Constructor is used to attach image to 
	TextureResource(int width, int height, std::vector<unsigned char> image, const long GUID) : Resource(GUID) {
		this->m_width = width;
		this->m_height = height;
		this->m_image = image;
		this->setSize(sizeof(unsigned char) * 4 * width * height);
	}
	~TextureResource() {};
};

//#endif
