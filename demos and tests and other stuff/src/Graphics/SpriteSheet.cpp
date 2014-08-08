#include "SpriteSheet.h"
#include "Sprite.h"

SpriteSheet::SpriteSheet() : sheet(nullptr), sheetWidth(0), sheetHeight(0), nSprites(0), nRowsAndColumns(0), loaded(false), name("SpriteSheet")
{
}

SpriteSheet::SpriteSheet(SDL_Renderer* renderer) : sheet(nullptr), sheetWidth(0), sheetHeight(0), nSprites(0), nRowsAndColumns(0), loaded(false), name("SpriteSheet")
{
	this->renderer = renderer;
}

SpriteSheet::~SpriteSheet() {
	freeTexture();
	renderer = nullptr;
	loaded = nullptr;
}

bool SpriteSheet::loadTextureAndClips(std::string path, Uint16 sheetWidth, Uint16 sheetHeight, Uint16 nSprites) {
	//Get rid of preexisting texture and create a new texture
	freeTexture();
	SDL_Texture* newTexture = nullptr;

	//Assign received parameters
	this->sheetWidth = sheetWidth;
	this->sheetHeight = sheetHeight;
	this->nSprites = nSprites;
	this->nRowsAndColumns = (Uint16) sqrt(nSprites);
	this->spriteWidth = sheetWidth / nRowsAndColumns;
	this->spriteHeight = sheetHeight / nRowsAndColumns;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr) {
		Log::s()->logError("Unable to load image " + path + "! SDL_image Error: " + std::string(IMG_GetError()));
	} else {
		//Color key image (cyan)
		if (SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF)) < 0) {
			Log::s()->logError("Unable to set the color key for the sprite sheet! SDL Error: " + std::string(SDL_GetError()));
		}

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == nullptr) {
			Log::s()->logError("Unable to create texture from " + path + "! SDL Error: " + std::string(SDL_GetError()));
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	sheet = newTexture;
	loaded = sheet != nullptr;
	if (loaded) {
		Log::s()->logDebug("Sprite Sheet (" + name + ") was loaded");
	}

	return loaded;
}

void SpriteSheet::freeTexture() {
	//Free texture if it exists
	if (sheet != nullptr) {
		SDL_DestroyTexture(sheet);
		sheet = nullptr;
		loaded = false;
		Log::s()->logDebug("Sprite Sheet (" + name + ") was UNloaded");
	}
}

SDL_Texture* SpriteSheet::getTexture() const {
	return sheet;
}

Uint16 SpriteSheet::getNRowsAndColumns() const {
	return nRowsAndColumns;
}

Uint16 SpriteSheet::getSheetWidth() const {
	return sheetWidth;
}

Uint16 SpriteSheet::getSheetHeight() const {
	return sheetHeight;
}

Uint16 SpriteSheet::getSpriteWidth() const {
	return spriteWidth;
}

Uint16 SpriteSheet::getSpriteHeight() const {
	return spriteHeight;
}