#include <iostream>

#include "PNGLoader.h"
#include "LodePNG.h"
#include <iostream>
#include <sstream>
#include "TextureResource.h"
#include "removeStack.h"
#include "ziplib/zip.h"

our::string our::convert(unsigned int data) {
	return our::string((unsigned char*)(std::to_string(data).c_str()));
}
our::string our::convert(unsigned char* data) {
	return our::string(data);
}

our::string PNGLoader::load(const std::string& path)
{
	using namespace our;
	std::vector<unsigned char> image;
	unsigned int width;
	unsigned int height;
	string res;

	// 'decode' both checks for error and assigns values to 'image', 'width, and 'height'
	if (unsigned int error = lodepng::decode(image, width, height, path)) {
		std::cout << "ERROR: " << error << lodepng_error_text(error) << " at filePath: " << path << std::endl;
	}
	else {
		// Add header info (Width & Height)
		res.append(convert(width));
		res.append((unsigned char*)"\n");
		res.append(convert(height));

		// Convert each point of data in the vector and append
		for (int i = 0; i < image.size(); i++) {
			// Delimiter
			if ((i % 4) == 0) {	/// '4' since it's 4 channels per pixel
				res.append((unsigned char*)"\n");
			}
			else {
				res.append((unsigned char*)",");
			}
			// Current vertice info
			res.append(convert(image.at(i)));
		}
	}

	//for (char c : res) {
	//	static_cast<unsigned char*>(static_cast<void *>(&c));
	//}


	return res;
}