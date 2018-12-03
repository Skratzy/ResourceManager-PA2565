#include "PNGLoader.h"
#include "LodePNG.h"
#include <iostream>

using namespace lodepng;
using namespace std;

Resource* PNGLoader::load(const std::string& filePath, const long GUID)
{
	std::vector<unsigned char> image;
	unsigned int width;
	unsigned int height;
	Resource* ptr = nullptr;
	
	// 'decode' both checks for error and assigns values to 'image', 'width, and 'height'
	if (unsigned int error = decode(image, width, height, filePath)) {
		cout << "ERROR: " << error << lodepng_error_text(error)	<< " at filePath: " << filePath << endl;
	}
	else {
		ptr = new ResourcePNG(width, height, image, GUID);
	}

	return ptr;
}
