#include "TTFText.h"
#include "../Screen.h"

int						textWidth;
int						textHeight;

TTFText::TTFText() : textTexture(nullptr), textWidth(0), textHeight(0)
{
	this->screen = nullptr;
}

TTFText::TTFText(Screen* screen) : screen(screen), textTexture(nullptr), textWidth(0), textHeight(0)
{
}

TTFText::~TTFText() {
	SDL_DestroyTexture(textTexture);
	textTexture = nullptr;
	screen = nullptr;
}

//TODO add logs to TTFText
int TTFText::load() {
	textTexture = screen->loadTextTexture("The quick brown fox jumps over the lazy dog", Fonts::Lazy);
	//Log::s()->logDebug("The font with the path [" + path + "] was loaded");
	return 0;
}

void TTFText::render() {
	screen->renderTTFText(this);
}