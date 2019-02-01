#pragma once
#include <vector>

namespace C3Engine
{
	class IOManager
	{
		public:
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};
}