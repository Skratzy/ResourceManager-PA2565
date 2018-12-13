#include "PNGLoader.h"
#include "../Resources/TextureResource.h"

#include "LodePNG.h"
#include <experimental/filesystem>

Resource* PNGLoader::load(const char* path, const long GUID)
{
	std::vector<unsigned char> image;
	unsigned int width;
	unsigned int height;
	Resource* resource = nullptr;
	
	std::string filePath = path;
	size_t check = 0;
	check = filePath.find(".zip");
	bool loadZipped = false;
	if (check < filePath.length()) {
		loadZipped = true;
		filePath = extractFile(path, check);
	}

	// 'decode' both checks for error and assigns values to 'image', 'width, and 'height'
	if (unsigned int error = lodepng::decode(image, width, height, filePath.c_str())) {
		RM_DEBUG_MESSAGE(std::to_string(error) + lodepng_error_text(error) + " at filePath: " + path, 0);
	}
	else {
		unsigned int size = sizeof(TextureResource) + sizeof(unsigned int) * image.size();
		resource = new (RM_MALLOC(size)) TextureResource(width, height, image, GUID);
		resource->setSize(size);
	}
	if (loadZipped) {
		// Deleting extracted file once loaded in to memory
		std::experimental::filesystem::remove(filePath.c_str());
	}

	return resource;
}
