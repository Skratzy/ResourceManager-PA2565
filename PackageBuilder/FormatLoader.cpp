#include "FormatLoader.h"

#include "ziplib/zip.h"
#include "removeStack.h"
#include <stdio.h>

void FormatLoader::write(our::string & data, std::string zippedName, zip * archive)
{
	// Create a file...
	FILE* file;
	std::string path = globalStack::getInstance().fetchPath();

	errno_t error = fopen_s(&file, path.c_str(), "w");
	if (error == 0)
	{
		// ... and fill it with the data.
		fputs((char*)data.c_str(), file);
		fclose(file);

		// Copy file into archive
		zip_source* source = zip_source_file(archive, path.c_str(), 0, 0);
		int index = zip_file_add(archive, zippedName.c_str(), source, 0);
	}
}
