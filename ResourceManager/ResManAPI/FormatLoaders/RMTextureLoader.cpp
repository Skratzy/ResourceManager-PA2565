#include "RMTextureLoader.h"
#include <fstream>
#include <sstream>
#include "../Resources/TextureResource.h"
#include "../Resources/Resource.h"
#include "../../Defines.h"

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

	// If it's in a zip, deal with it appropriately
	std::string filePath = path;
	size_t check = 0;
	check = filePath.find(".zip");
	bool loadZipped = false;
	if (check < filePath.length()) {
		loadZipped = true;
	}
	string width;
	string height;
	string lineData;
	std::vector<unsigned char> imageData;

	string colourData[4];
	enum COLOR { RED, BLUE, GREEN, ALPHA, COUNT };
	unsigned int lineIndex = 0;

	// Start the loading process with the correct filepath
	if (!loadZipped) {
		ifstream inputStream(path, std::ios_base::in | std::ios_base::binary);


		getline(inputStream, width);			// Load Width
		getline(inputStream, height);			// Load Height


	// Read the filestream one line at a time and input the data into
	// the imageData
		while (inputStream >> lineData) {
			lineIndex = 0;
			// Per color, read the color until a comma is met, last element should be a newline
			for (int currentColor = COLOR::RED; currentColor < COLOR::COUNT; currentColor++) {
				// Fetch all the data until a newline is met

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
	}
	else
	{
		void* ptr = readFile(path, check);
		
		std::string tempString = (char*)ptr;
		std::stringstream inputStream;
		inputStream << tempString;


		getline(inputStream, width);			// Load Width
		getline(inputStream, height);			// Load Height


		// Read the filestream one line at a time and input the data into
		// the imageData
		while (inputStream >> lineData) {
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
		free(ptr);
	}

	// Attach read data to resource
	unsigned int size = sizeof(TextureResource) + sizeof(unsigned int) * imageData.size();
	Resource* res = new (RM_MALLOC(size)) TextureResource(
		std::stoi(width),	// int std::string_to_int(string)
		std::stoi(height),	//
		imageData,
		GUID,
		path
	);
	res->setSize(size);

	return res;
}
