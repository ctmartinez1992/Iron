#include "Fonts.h"

const Fonts Lazy = Fonts("res/lazy.ttf", 20, Colors::Green);

Fonts::Fonts() : font(nullptr), path(""), size(0), color(nullptr)
{
}

Fonts::Fonts(std::string path, Uint8 size, Colors color) : path(path), size(size), color(&color)
{
	//Initialize SDL_ttf
	if (TTF_WasInit() == 0) {
		if (TTF_Init() == -1) {
			//Log::s()->logError("SDL_ttf could not initialize! SDL_image Error: " + std::string(IMG_GetError()));
			//std::cout << "SDL_ttf could not initialize! SDL_image Error: " << std::string(IMG_GetError());
		} else {
			//std::cout << "The font with the path [" << path << "] was loaded";
		}
	} else {
		//std::cout << "SDL_ttf is already initialized, no need to do it again";
	}

	//Create the font
	font = TTF_OpenFont(path.c_str(), size);
	if (font == NULL) {
		//std::cout << "The font with the path [" << path << "] failed to be loaded! TTF Error: " << std::string(TTF_GetError());
	}
}

Fonts::~Fonts() {
}

void Fonts::freeFonts() {	
	TTF_CloseFont(Lazy.font);
	//Log::s()->logDebug("The font with the path [" + Lazy.path + "] was UNloaded");
}