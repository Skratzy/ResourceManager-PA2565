#ifndef _RM_TEXTURE_RESOURCE_H
#define _RM_TEXTURE_RESOURCE_H

#include "Resource.h"
#include <vector>

class TextureResource : public Resource {
public:
	unsigned int m_width;
	unsigned int m_height;
	std::vector<unsigned char> m_image;
	// Constructor is used to attach image to the resource
	TextureResource(int width, int height, std::vector<unsigned char> image, const long GUID, bool 4channel) : Resource(GUID) {
		this->m_width = width;
		this->m_height = height;
		this->m_image = image;
		if (true) {
			this->setSize(sizeof(unsigned char) * 4 * width * height);
		}
		else {
			this->setSize(sizeof(unsigned char) * 3 * width * height);
		}
		
	}
	~TextureResource() {};
};

#endif // _RM_TEXTURE_RESOURCE_H
