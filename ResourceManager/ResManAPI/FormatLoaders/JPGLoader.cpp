#include "JPGLoader.h"
#include "../Resources/TextureResource.h"
#include <experimental/filesystem>

#define cimg_use_jpeg
#include "CImg.h"


Resource * JPGLoader::load(const char* path, const long GUID)
{
	using namespace cimg_library;

	// Checking if the asset is in a package
	std::string filePath = path;
	size_t check = 0;
	check = filePath.find(".zip");
	bool loadZipped = false;
	if (check < filePath.length()) {
		loadZipped = true;
		filePath = extractFile(path, check);
	}

	CImg<unsigned char> source(filePath.c_str());
	unsigned int width = source.width();
	unsigned int height = source.height();
	std::vector<unsigned char> image;
	Resource* resource = nullptr;


	
	if (source.size() == 0) {
		std::string debugMessage = (filePath.c_str() + std::string(" did not load succesfully!"));
		RM_DEBUG_MESSAGE(debugMessage, 0);
	}
	else {
		// Conversion of a single char array into the vector
		for (unsigned int y = 0; y < height; y++) {
			for (unsigned int x = 0; x < width; x++) {
				// source.data(pixel_x, pixel_y, depth, color(0,1,2 = red,green,blue)
				image.push_back(*source.data(x, y, 0, 0)); 
				image.push_back(*source.data(x, y, 0, 1));
				image.push_back(*source.data(x, y, 0, 2));
				image.push_back(unsigned char(255));
			}
		}

		unsigned int size = sizeof(TextureResource) + sizeof(unsigned int) * image.size();
		// Attach the formatted image to a textureresource
		resource = new (RM_MALLOC(size)) TextureResource(width, height, image, GUID);
		resource->setSize(size);
	}

	if (loadZipped) {
		// Deleting extracted file once loaded in to memory
		std::experimental::filesystem::remove(filePath.c_str());
	}

	return resource;
}
