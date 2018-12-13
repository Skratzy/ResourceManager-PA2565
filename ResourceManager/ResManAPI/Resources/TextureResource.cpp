#include "TextureResource.h"

TextureResource::TextureResource(int width, int height, std::vector<unsigned char> image, const long GUID)
	: Resource(GUID)
{
	sg_image_desc sgid{ 0 };
	sg_image_content sgic{ 0 };
	sgic.subimage[0][0].ptr = image.data();
	sgic.subimage[0][0].size = image.size();
	sgid.width = width;
	sgid.height = height;
	sgid.pixel_format = SG_PIXELFORMAT_RGBA8;
	sgid.min_filter = SG_FILTER_NEAREST;
	sgid.mag_filter = SG_FILTER_NEAREST;
	sgid.content = sgic;
	m_imgBuffer = sg_make_image(&sgid);
}

TextureResource::~TextureResource() {
	sg_destroy_image(m_imgBuffer);
}

sg_image & TextureResource::getImage()
{
	return m_imgBuffer;
}
