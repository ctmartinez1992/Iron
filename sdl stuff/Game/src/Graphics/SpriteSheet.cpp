#include "SpriteSheet.h"
#include "Sprite.h"

SpriteSheet::SpriteSheet() : sheet(nullptr), sheetWidth(0), sheetHeight(0), nSprites(0), nRowsAndColumns(0), loaded(false)
{
}

SpriteSheet::SpriteSheet(SDL_Renderer* renderer) : sheet(nullptr), sheetWidth(0), sheetHeight(0), nSprites(0), nRowsAndColumns(0), loaded(false)
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
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	} else {
		//Color key image (cyan)
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == nullptr) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	////Create the sprites
	//sprites = new Sprite*[nRowsAndColumns];
	//for (int i = 0; i<nRowsAndColumns; i++) {
	//	sprites[i] = new Sprite[nRowsAndColumns];
	//	for (int j = 0; j < nRowsAndColumns; j++) {
	//		sprites[i][j].setSpriteClip(i * spriteWidth, j * spriteHeight, spriteWidth, spriteHeight);
	//		sprites[i][j].sheet = this;
	//		sprites[i][j].texture = newTexture;
	//	}
	//}

	//Return success
	sheet = newTexture;
	loaded = sheet != nullptr;
	return loaded;
}

void SpriteSheet::freeTexture() {
	//Free texture if it exists
	if (sheet != nullptr) {
		SDL_DestroyTexture(sheet);
		sheet = nullptr;
		loaded = false;
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