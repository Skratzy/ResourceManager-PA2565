#include "JPGLoader.h"
#include "TextureResource.h"
#include <iostream>

#define cimg_use_jpeg
#include "CImg.h"

using namespace cimg_library;
using namespace std;

Resource * JPGLoader::load(const std::string & path, const long GUID)
{
	CImg<unsigned char> source("Assets/testImage1.jpg");
	unsigned int width = source.width();
	unsigned int height = source.height();
	std::vector<unsigned char> image; 
	Resource* resource = nullptr;
	
	if (source.size() == 0) {
		cout << "ERROR: " << path << "did not load succesfully!" << endl;		
	}
	else {
		// Conversion of a single char array into the vector
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				// source.data(pixel_x, pixel_y, depth, color(0,1,2 = red,green,blue)
				image.push_back(*source.data(x, y, 0, 0));
				image.push_back(*source.data(x, y, 0, 1));
				image.push_back(*source.data(x, y, 0, 2));
			}
		}

		// Attach the formatted image to a textureresource
		resource = new TextureResource(width, height, image, GUID);
	}

	return resource;
}
