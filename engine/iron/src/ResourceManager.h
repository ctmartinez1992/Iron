#ifndef IRON_GRAPHICS_RESOURCE_MANAGER_H_
#define IRON_GRAPHICS_RESOURCE_MANAGER_H_

#include "TextureCache.h"
#include <string>

namespace iron {

	namespace graphics {

		//This is a way for us to access all our resources, such as Models or textures.
		class ResourceManager
		{
		public:
			static GLTexture getTexture(std::string texturePath);

		private:
			static TextureCache _textureCache;
		};
	}
}

#endif