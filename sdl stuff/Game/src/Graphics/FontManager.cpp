#include "FontManager.h"

FontManager::FontManager() : screen(nullptr), fonts(), currentFont(nullptr), nFonts(0)
{
}

FontManager::FontManager(Screen* screen) : screen(screen), fonts(), currentFont(nullptr), nFonts(0)
{
}

FontManager::~FontManager()
{
	screen = nullptr;
	currentFont = nullptr;
	nFonts = 0;
}

FontManager* FontManager::s(){
	if (_s == nullptr){
		_s = new FontManager();
	}

	return _s;
}

int FontManager::addFont(const std::string id, const std::string path, const Colors* color, const Uint8 size) {
	//Initialize SDL_ttf
	if (TTF_WasInit() == 0) {
		if (TTF_Init() == -1) {
			Log::s()->logError("SDL_ttf could not initialize! SDL_image Error: " + std::string(IMG_GetError()));
			return -1;
		} else {
			Log::s()->logInfo("SDL_ttf was initialized");
		}
	}
	else {
		Log::s()->logDebug("SDL_ttf is already initialized, no need to do it again");
	}

	//Create the font
	Font* font = new Font(id, path, color, size);

	if (font == NULL) {
		Log::s()->logError("A Font object with the id [" + id + "] and path [" + path + "] could not be created");
		return -1;
	}

	if (font->font == nullptr) {
		Log::s()->logError("The TTF_Font of a Font object with the id [" + id + "] and path [" + path + "] could not be created");
		return -1;
	}

	//Load the text texture
	textTexture = screen->loadTextTexture("The quick brown fox jumps over the lazy dog", Fonts::Lazy);

	Log::s()->logDebug("The font with the id [" + id + "] and path [" + path + "] was loaded");
}