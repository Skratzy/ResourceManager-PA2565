#include "RMTextureLoader.h"
#include <fstream>
#include <sstream>
#include "../ResourceManager/ResManAPI/Resources/TextureResource.h"
#include "../ResourceManager/ResManAPI/Resources/Resource.h"
#include "Defines.h"

RMTextureLoader::RMTextureLoader()
{
	this->m_supportedExtensions.push_back(".rmtex");
}

RMTextureLoader::~RMTextureLoader()
{
}

Resource * RMTextureLoader::load(const char * path, const long GUID)
{
//	using namespace our;
	using namespace std;
	ifstream inputStream(path, std::ios_base::in | std::ios_base::binary);
	string width;
	string height;
	string lineData;
	std::vector<unsigned char> imageData;
	getline(inputStream, width);			// Load Width
	getline(inputStream, height);			// Load Height
	
	// Read the filestream one line at a time and input the data into
	// the imageData
	string colourData[4];
	enum COLOR {RED, BLUE, GREEN, ALPHA, COUNT};
	int lineIndex = 0;

	while (inputStream >> lineData)	{
		lineIndex = 0;
		// Per color, read the color until a comma is met, last element should be a newline
		for (int currentColor = COLOR::RED; currentColor < COLOR::COUNT; currentColor++) {
			// Fetch all the data until a newline is met
			unsigned char character;

			for (; lineIndex < lineData.size();) {
				string color;
				if (lineData.at(lineIndex) != ',') {
					unsigned char character = lineData.at(lineIndex);
					colourData[currentColor].push_back(character);					
					lineIndex++;
				}
				else {
					lineIndex++;
					break;
				}

			}

		}
		
		// Finish it up
		
		for (int currentColor = COLOR::RED; currentColor < COLOR::COUNT; currentColor++) {
			int castedInt = std::stoi(colourData[currentColor]);
			unsigned char castedChar = (unsigned char)castedInt;
			imageData.push_back(castedChar);

			// ... and clear contents in preparation of next iteration
			colourData[currentColor].clear();
		}
	}

	// Attach read data to resource
	unsigned int size = sizeof(TextureResource) + sizeof(unsigned int) * imageData.size();
	Resource* res = new (RM_MALLOC(size)) TextureResource(
		std::stoi(width),	// int std::string_to_int(string)
		std::stoi(height),	//
		imageData,
		GUID
	);
	res->setSize(size);
	
	// Return it out!
	return res;
}
