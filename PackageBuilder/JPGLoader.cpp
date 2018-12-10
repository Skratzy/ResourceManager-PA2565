#include "JPGLoader.h"
#include "TextureResource.h"
#include <iostream>
#include <ziplib/zip.h>

#define cimg_use_jpeg
#include "CImg.h"
#include "removeStack.h"

using namespace cimg_library;

our::string JPGLoader::load(const std::string& path)
{
	using namespace our;
	CImg<unsigned char> source(path.c_str());
	unsigned int width = source.width();
	unsigned int height = source.height();
	std::vector<unsigned char> image;
	string res;

	if (source.size() == 0) {
		std::cout << "ERROR: " << path << "did not load succesfully!" << std::endl;
	}
	else {
		// First convert from wierd funky jpg format to vector
		// Conversion of a single char array into the vector
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				// source.data(pixel_x, pixel_y, depth, color(0,1,2 = red,green,blue)
				image.push_back(*source.data(x, y, 0, 0));
				image.push_back(*source.data(x, y, 0, 1));
				image.push_back(*source.data(x, y, 0, 2));
				image.push_back(char(255));
			}
		}

		// Secondly convert from vector to a single our::string
		// Add header info (Width & Height)
		res.append(convert(width));
		res.append((unsigned char*)"\n");
		res.append(convert(height));

		// Convert each point of data in the vector and append
		for (int i = 0; i < image.size(); i++) {
			// Delimiter
			if ((i % 4) == 0) { /// '4' since it's 4 channels per pixel
				res.append((unsigned char*)"\n");
			}
			else {
				res.append((unsigned char*)",");
			}
			// Current vertice info
			res.append(convert(image.at(i)));
		}
	}

	return res;
}