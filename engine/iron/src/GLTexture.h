#ifndef IRON_GRAPHICS_GL_TEXTURE_H_
#define IRON_GRAPHICS_GL_TEXTURE_H_

#include <sdl/glew.h>

namespace iron {

	namespace graphics {

		struct GLTexture {
			GLuint id;
			int width;
			int height;
		};
	}
}

#endif