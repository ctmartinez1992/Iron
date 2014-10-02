#ifndef IRON_GRAPHICS_IO_MANAGER_H_
#define IRON_GRAPHICS_IO_MANAGER_H_

#include <vector>

namespace iron {

	namespace graphics {

		class IOManager {
		public:
			static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
		};
	}
}

#endif