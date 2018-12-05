#include <iostream>

#include "PNGLoader.h"
#include "LodePNG.h"
#include <iostream>
#include "TextureResource.h"

using namespace lodepng;
using namespace std;

Resource* PNGLoader::load(const std::string& filePath, const long GUID)
{
	std::vector<unsigned char> image;
	unsigned int width;
	unsigned int height;
	Resource* resource = nullptr;
	
	// 'decode' both checks for error and assigns values to 'image', 'width, and 'height'
	if (unsigned int error = decode(image, width, height, filePath)) {
		cout << "ERROR: " << error << lodepng_error_text(error)	<< " at filePath: " << filePath << endl;
	}
	else {
		resource = new TextureResource(width, height, image, GUID);
	}

	return resource;
}
