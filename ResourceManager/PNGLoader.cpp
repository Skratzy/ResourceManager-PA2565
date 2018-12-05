#include <iostream>

#include "PNGLoader.h"
#include "LodePNG.h"
#include <iostream>
#include "TextureResource.h"

Resource* PNGLoader::load(const std::string& filePath, const long GUID)
{
	std::vector<unsigned char> image;
	unsigned int width;
	unsigned int height;
	Resource* resource = nullptr;
	
	// 'decode' both checks for error and assigns values to 'image', 'width, and 'height'
	if (unsigned int error = lodepng::decode(image, width, height, filePath)) {
		std::cout << "ERROR: " << error << lodepng_error_text(error)	<< " at filePath: " << filePath << std::endl;
	}
	else {
		resource = new TextureResource(width, height, image, GUID);
	}

	return resource;
}
