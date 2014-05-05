#define _CRTDBG_MAP_ALLOC
#include "Screen.h"
#include "Sprite.h"

Screen*				Screen::_instance = 0;
SDL_BlendMode		Screen::DEFAULT_BLEND_MODE = SDL_BLENDMODE_BLEND;
SDL_Color			Screen::DEFAULT_COLOR_SCHEME = { 255, 255, 255, 255 };

Screen::Screen() : screenTitle("Not defined"), width(800), height(600),
											   widthHalf(800 / 2), heightHalf(600 / 2),
											   widthThird(800 / 3), heightThird(600 / 3),
											   widthFourth(800 / 4), heightFourth(600 / 4), 
											   viewportWidth(width), viewportHeight(height),
											   init(false), window(nullptr)
{
	normalViewport = { 0, 0, 800, 600 };
}

Screen::Screen(const char* screenTitle, Uint16 width, Uint16 height) : screenTitle(screenTitle), width(width), height(height),
																					   widthHalf(width / 2), heightHalf(height / 2),
																					   widthThird(width / 3), heightThird(height / 3),
																					   widthFourth(width / 4), heightFourth(height / 4),
																					   viewportWidth(width), viewportHeight(height),
																					   init(false), window(nullptr)
{
	normalViewport = { 0, 0, width, height };
}

Screen::~Screen() {
	//Destroy window.
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;

	//Invalidade singleton.
	_instance = 0;
}

Screen* Screen::getInstance() {
   if (!_instance) {
      _instance = new Screen;
   }
   return _instance;
}

bool Screen::initScreen() {
	//Initialization flag.
	bool success = true;

	//Initialize SDL.
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	} else {
		//Set texture filtering to linear
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		window = SDL_CreateWindow(this->screenTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_SHOWN);
		if(window == nullptr) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		} else {
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(renderer == nullptr) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			} else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

void Screen::clearScreen() {
	if(SDL_RenderClear(renderer) == -1) {
		printf("An error occured when clearing the screen! SDL Error: %s\n", SDL_GetError());
	}
}

void Screen::updateScreen() {
	SDL_RenderPresent(renderer);
}

SDL_Texture* Screen::loadTexture(const std::string path) {
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path.
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		//Create texture from surface pixels.
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == nullptr) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

void Screen::renderTexture(SDL_Texture* texture, SDL_Rect* positionAndSize, SDL_Rect* sheetClip, Uint8 rMod, Uint8 gMod, Uint8 bMod, Uint8 alpha) const {
	//Assign color mod and alpha mod
	SDL_SetTextureColorMod(texture, rMod, gMod, bMod);
	if (alpha < 255) {
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(texture, alpha);
	}

	//Render
	if (SDL_RenderCopy(renderer, texture, nullptr, positionAndSize) == -1) {
		printf("An error occured when rendering a texture! SDL Error: %s\n", SDL_GetError());
	}

	//Restore color mod and alpha mod
	SDL_SetTextureColorMod(texture, DEFAULT_COLOR_SCHEME.r, DEFAULT_COLOR_SCHEME.g, DEFAULT_COLOR_SCHEME.b);
	if (alpha < 255) {
		SDL_SetTextureBlendMode(texture, DEFAULT_BLEND_MODE);
		SDL_SetTextureAlphaMod(texture, DEFAULT_COLOR_SCHEME.a);
	}
}

void Screen::renderSprite(Sprite* sprite) const {
	//Create SDL_Rect with position and dimensions and assign color mod and alpha mod
	SDL_Rect positionAndSize = { sprite->getPosition()->x, sprite->getPosition()->y, sprite->getSpriteClip()->w, sprite->getSpriteClip()->h };
	SDL_Color* color = sprite->getColorMod();
	SDL_SetTextureColorMod(sprite->texture, color->r, color->g, color->b);
	if (color->a < 255) {
		SDL_SetTextureBlendMode(sprite->texture, DEFAULT_BLEND_MODE);
		SDL_SetTextureAlphaMod(sprite->texture, color->a);
	}

	//Obtain clip
	SDL_Rect* clip = (sprite->useClip) ? sprite->getSpriteClip() : nullptr;

	//If it's animated, clip it properly
	if (sprite->useAnimation) {
		if (sprite->animations->currentAnimation != nullptr) {
			clip->x = (sprite->animations->currentAnimation->getCurrentFrame() % sprite->sheet->getNRowsAndColumns()) * clip->w;
			clip->y = (sprite->animations->currentAnimation->getCurrentFrame() / sprite->sheet->getNRowsAndColumns()) * clip->h;
		}
	}

	//Render
	if (SDL_RenderCopy(renderer, sprite->texture, clip, &positionAndSize) == -1) {
		printf("An error occured when rendering a sprite! SDL Error: %s\n", SDL_GetError());
	}

	//Restore color mod and alpha mod
	SDL_SetTextureColorMod(sprite->texture, DEFAULT_COLOR_SCHEME.r, DEFAULT_COLOR_SCHEME.g, DEFAULT_COLOR_SCHEME.b);
	if (color->a < 255) {
		SDL_SetTextureBlendMode(sprite->texture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(sprite->texture, DEFAULT_COLOR_SCHEME.a);
	}
}

void Screen::renderNormalTexture(NormalTexture* normalTexture) const {
	if (SDL_RenderCopy(renderer, normalTexture->getTexture(), nullptr, normalTexture->getPositionAndSize()) == -1) {
		printf("An error occured when rendering a texture! SDL Error: %s\n", SDL_GetError());
	}
}

void Screen::renderFilledSquare(SDL_Rect* fillRect, const Colors color) const {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, fillRect);
}

void Screen::renderDrawnSquare(SDL_Rect* drawRect, const Colors color) const {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(renderer, drawRect);
}

void Screen::renderPoint(const SDL_Point* point, const Colors color) const {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawPoint(renderer, point->x, point->y);
}

void Screen::setViewport(const SDL_Rect* viewport) {
	SDL_RenderSetViewport(renderer, viewport);
	this->viewportWidth = viewport->w;
	this->viewportHeight = viewport->h;
}

void Screen::restoreNormalViewport() {
	SDL_RenderSetViewport(renderer, &normalViewport);
	this->viewportWidth = width;
	this->viewportHeight = height;
}