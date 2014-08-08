#include "FontManager.h"

FontManager*	FontManager::_s = nullptr;

FontManager::FontManager() : screen(nullptr), fonts(), currentFont(nullptr), nFonts(0)
{
}

FontManager::FontManager(Screen* screen) : screen(screen), fonts(), currentFont(nullptr), nFonts(0)
{
}

FontManager::~FontManager() {
	for (std::map<std::string, Font*>::iterator iterator = fonts.begin(); iterator != fonts.end(); ++iterator) {
		delete (*iterator).second;
	}

	fonts.clear();
	currentFont = nullptr;
	screen = nullptr;
	nFonts = 0;

	Log::s()->logInfo("FontManager was destroyed");
}

FontManager* FontManager::s(){
	if (_s == nullptr) {
		Log::s()->logInfo("FontManager is being created");
		_s = new FontManager();
		Log::s()->logInfo("FontManager was created");
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
	} else {
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

	//TODO Check for repeated ids when creating a new font
	//Add the font to the map
	fonts[font->id] = font;

	Log::s()->logDebug("A Font object with the id [" + id + "] and path [" + path + "] was loaded");

	return 0;
}

int FontManager::useFont(const std::string id) {
	if (fonts.count(id) != 0) {
		currentFont = fonts.at(id);
		return 0;
	} else {
		Log::s()->logWarning("The font with the id [" + id + "] does not exist in the fonts map and therefore cannot be assigned to currentFont");
		return -1;
	}
}

void FontManager::close() {
	delete _s;
	_s = nullptr;
}