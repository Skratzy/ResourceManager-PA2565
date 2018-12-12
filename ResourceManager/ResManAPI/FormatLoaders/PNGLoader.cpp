#include "PNGLoader.h"
#include "../Resources/TextureResource.h"

#include "LodePNG.h"

Resource* PNGLoader::load(const char* path, const long GUID)
{
	std::vector<unsigned char> image;
	unsigned int width;
	unsigned int height;
	Resource* resource = nullptr;
	
	// 'decode' both checks for error and assigns values to 'image', 'width, and 'height'
	if (unsigned int error = lodepng::decode(image, width, height, path)) {
		RM_DEBUG_MESSAGE(std::to_string(error) + lodepng_error_text(error) + " at filePath: " + path, 0);
	}
	else {
		unsigned int size = sizeof(TextureResource) + sizeof(unsigned int) * image.size();
		resource = new (RM_MALLOC(size)) TextureResource(width, height, image, GUID);
		resource->setSize(size);
	}

	return resource;
}
