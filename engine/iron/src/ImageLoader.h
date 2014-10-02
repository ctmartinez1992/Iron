#ifndef IRON_GRAPHICS_IMAGE_LOADER_H_
#define IRON_GRAPHICS_IMAGE_LOADER_H_

#include "GLTexture.h"
#include <string>

namespace iron {

	namespace graphics {

		//Loads images into GLTextures.
		class ImageLoader {
		public:
			static GLTexture loadPNG(std::string filePath);
		};
	}
}

#endif