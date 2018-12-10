#ifndef _RM_TEXTURE_RESOURCE_H
#define _RM_TEXTURE_RESOURCE_H

#include <vector>

#include "Resource.h"
#include "../../Defines.h"


class TextureResource : public Resource {
private:
	unsigned int m_width;
	unsigned int m_height;
	std::vector<unsigned char> m_image;
	sg_image m_imgBuffer;

public:
	// Constructor is used to attach image to the resource
	TextureResource(int width, int height, std::vector<unsigned char> image, const long GUID);
	~TextureResource() {};

	sg_image& getImage();
};

#endif // _RM_TEXTURE_RESOURCE_H
