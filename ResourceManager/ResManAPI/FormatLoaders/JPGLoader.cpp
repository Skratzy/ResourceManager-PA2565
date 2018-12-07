#include "JPGLoader.h"
#include "../Resources/TextureResource.h"

#define cimg_use_jpeg
#include "CImg.h"

Resource * JPGLoader::load(const char* path, const long GUID)
{
	using namespace cimg_library;

	CImg<unsigned char> source(path);
	unsigned int width = source.width();
	unsigned int height = source.height();
	std::vector<unsigned char> image;
	Resource* resource = nullptr;
	
	if (source.size() == 0) {
		std::string debugMessage = (path + std::string(" did not load succesfully!"));
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
				image.push_back(char(255));
			}
		}

		// Attach the formatted image to a textureresource
		resource = new TextureResource(width, height, image, GUID);
	}

	return resource;
}
