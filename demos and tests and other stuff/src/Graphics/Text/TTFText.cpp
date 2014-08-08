#include "TTFText.h"
#include "../Screen.h"

TTFText::TTFText() : text(""), texture(nullptr), width(0), height(0)
{
	this->screen = nullptr;
}

TTFText::TTFText(Screen* screen) : screen(screen), text(""), texture(nullptr), width(0), height(0)
{
}

TTFText::~TTFText() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
	screen = nullptr;

	Log::s()->logDebug("A TTFText object was UNloaded");
}

int TTFText::load() {
	if (FontManager::s()->currentFont == nullptr) {
		Log::s()->logWarning("A font needs to be in place to be used, the method useFont(const std::string id) needs to be called");
	}

	//Load the text texture
	texture = screen->loadTextTexture("The quick brown fox jumps over the lazy dog", FontManager::s()->currentFont, width, height);
	if (texture == nullptr) {
		Log::s()->logWarning("A TTFText object failed to load");
		return -1;
	}

	Log::s()->logDebug("A TTFText object was loaded");

	return 0;
}

void TTFText::render() {
	if (texture != nullptr) {
		screen->renderTTFText(this);
	}
}