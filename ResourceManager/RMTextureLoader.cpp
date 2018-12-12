#include "RMTextureLoader.h"
#include <fstream>
#include "../ResourceManager/ResManAPI/Resources/TextureResource.h"
#include "../ResourceManager/ResManAPI/Resources/Resource.h"

RMTextureLoader::RMTextureLoader()
{
	this->m_supportedExtensions.push_back(".rmtex");
}

RMTextureLoader::~RMTextureLoader()
{
}

Resource * RMTextureLoader::load(const char * path, const long GUID)
{
	using namespace std;
	ifstream inputStream(path);
	string width;
	string height;
	string lineData;
	std::vector<unsigned char> imageData;
	getline(inputStream, width);			// Load Width
	getline(inputStream, height);			// Load Height
	
	// Read the filestream one line at a time and input the data into
	// the imageData
	unsigned char r, g, b, a, comma;
	while (inputStream
		>> r >> comma
		>> g >> comma
		>> b >> comma
		>> a
	)	{
		imageData.push_back(r);
		imageData.push_back(b);
		imageData.push_back(g);
		imageData.push_back(a);
	}

	// Attach read data to resource
	Resource* res = new TextureResource(
		stoi(width),	// int std::string_to_int(string)
		stoi(height),	//
		imageData,
		GUID
	);
	
	// Return it out!
	return res;
}
