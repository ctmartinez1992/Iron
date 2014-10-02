#include <sdl/SDL.h>
#include <sdl/glew.h>

#include "IronGraphics.h"

namespace iron {

	namespace graphics {

		int init() {
			//Initialize SDL.
			SDL_Init(SDL_INIT_EVERYTHING);

			//Double buffered window.
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

			return 0;
		}
	}
}