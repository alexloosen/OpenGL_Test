#include "IOManager.h"
#include <fstream>

namespace C3Engine
{

	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			perror(filePath.c_str());
			return false;
		}
		file.seekg(0, std::ios::end);

		int fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		// reduce fileSize by any header bytes that might be present
		fileSize -= file.tellg();

		buffer.resize(fileSize);
		file.read((char*)&(buffer[0]), fileSize);
		file.close();
		return true;
	}
}