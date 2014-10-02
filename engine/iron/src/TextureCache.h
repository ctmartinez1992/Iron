#ifndef IRON_GRAPHICS_TEXTURE_CACHE_H_
#define IRON_GRAPHICS_TEXTURE_CACHE_H_

#include <map>
#include "GLTexture.h"

namespace iron {

	namespace graphics {

		//This caches the textures so that multiple sprites can use the same textures
		class TextureCache
		{
		public:
			TextureCache();
			~TextureCache();

			GLTexture getTexture(std::string texturePath);

		private:
			std::map<std::string, GLTexture> _textureMap;
		};
	}
}

#endif