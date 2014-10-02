#ifndef IRON_GRAPHICS_VERTEX_H_
#define IRON_GRAPHICS_VERTEX_H_

#include <sdl/SDL.h>
#include <sdl/glew.h>
#include <string>

namespace iron {

	namespace graphics {

		enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

		class Window
		{
		public:
			Window();
			~Window();

			int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

			void swapBuffer();

			int getScreenWidth() { _screenWidth; }
			int getScreenHeight() { _screenHeight; }
		private:
			SDL_Window* _sdlWindow;
			int _screenWidth, _screenHeight;
		};
	}
}

#endif