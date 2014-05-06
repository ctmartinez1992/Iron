#include "NormalTexture.h"

NormalTexture::NormalTexture() : texture(nullptr), loaded(false)
{
	positionAndSize = new SDL_Rect({ 0, 0, 0, 0 });
}

NormalTexture::NormalTexture(SDL_Point position, SDL_Renderer* renderer) : texture(nullptr), loaded(false)
{
	positionAndSize = new SDL_Rect({ position.x, position.y, 0, 0 });
	this->renderer = renderer;
}

NormalTexture::~NormalTexture() {
	freeTexture();
	delete positionAndSize;
	positionAndSize = nullptr;
	renderer = nullptr;
	loaded = nullptr;
}

bool NormalTexture::loadTexture(std::string path) {
	//Get rid of preexisting texture and create a new texture
	freeTexture();
	SDL_Texture* newTexture = nullptr;

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
		} else {
			//Store image dimentions
			positionAndSize->w = loadedSurface->w;
			positionAndSize->h = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	texture = newTexture;
	loaded = texture != nullptr;
	return loaded;
}

void NormalTexture::freeTexture() {
	//Free texture if it exists
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
		loaded = false;
	}
}

SDL_Texture* NormalTexture::getTexture() const {
	return texture;
}

SDL_Rect* NormalTexture::getPositionAndSize() const {
	return positionAndSize;
}

int NormalTexture::getX() const {
	return positionAndSize->x;
}

int NormalTexture::getY() const {
	return positionAndSize->y;
}

int NormalTexture::getWidth() const {
	return positionAndSize->w;
}

int NormalTexture::getHeight() const {
	return positionAndSize->h;
}