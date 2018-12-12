#ifndef _PT_FORMAT_LOADER_
#define _PT_FORMAT_LOADER_

#include <vector>
#include <string>

class zip;

// Our own namespace for 'strings' using 'unsigned char'
namespace our {
	typedef std::basic_string<unsigned char> string;
	typedef std::basic_stringstream<unsigned char> stringstream;

	our::string convert(unsigned int data);
	our::string convert(unsigned char* data);
}


class FormatLoader
{
protected:
	std::vector<std::string> m_supportedExtensions;

public:
	virtual ~FormatLoader() {}
	virtual std::string load(const std::string& path) = 0;
	bool extensionSupported(const std::string& extension) {
		for (auto ext : m_supportedExtensions) {
			if (ext == extension)
				return true;
		}
		return false;
	}

	void write(our::string &data, std::string zippedName, zip* archive);

};

#endif //_RM_FORMAT_LOADER_