#include "ResourceManager.h"

namespace iron {

	namespace graphics {

		TextureCache ResourceManager::_textureCache;

		GLTexture ResourceManager::getTexture(std::string texturePath) {
			return _textureCache.getTexture(texturePath);
		}
	}
}