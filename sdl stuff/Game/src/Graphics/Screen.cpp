#define _CRTDBG_MAP_ALLOC
#include "Screen.h"
#include "../General/GameObject.h"
#include "Sprite.h"
#include "../Graphics/Geometry/GeometryDot.h"
#include "../Graphics/Geometry/GeometryLine.h"

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

	Log::s()->logInfo("Screen was destroyed");

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

	Log::s()->logInfo("Screen is being created...");

	//Initialize SDL.
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		success = false;
	} else {
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			Log::s()->logWarning("Linear texture filtering not enabled!");
		}

		//Create window
		window = SDL_CreateWindow(this->screenTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_SHOWN);
		if (window == nullptr) {
			Log::s()->logError("Window could not be created! SDL Error: " + std::string(SDL_GetError()));
			success = false;
		} else {
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == nullptr) {
				Log::s()->logError("Renderer could not be created! SDL Error: " + std::string(SDL_GetError()));
				success = false;
			} else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					Log::s()->logError("SDL_image could not initialize! SDL_image Error: " + std::string(IMG_GetError()));
					success = false;
				}
			}
		}
	}

	if (success) {
		Log::s()->logInfo("Screen was created successfully");
	}

	return success;
}

void Screen::clearScreen() {
	if (SDL_RenderClear(renderer) < 0) {
		Log::s()->logError("An error occured when clearing the screen! SDL Error: " + std::string(SDL_GetError()));
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
		Log::s()->logError("Unable to load image " + path + "! SDL_image Error : " + std::string(IMG_GetError()));
	}
	else {
		//Create texture from surface pixels.
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == nullptr) {
			Log::s()->logError("Unable to create texture from " + path + "! SDL Error: " + std::string(SDL_GetError()));
		}

		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

void Screen::renderSprite(const Sprite* sprite) const {
	//Create SDL_Rect with position and dimensions and assign color mod and alpha mod
	SDL_Rect positionAndSize = { (int) sprite->getPosition()->x, (int) sprite->getPosition()->y, sprite->getSpriteClip()->w, sprite->getSpriteClip()->h };
	SDL_Color* color = sprite->getColorMod();
	if (SDL_SetTextureColorMod(sprite->texture, color->r, color->g, color->b) < 0) {
		Log::s()->logError("Unable to set the texture color mod! SDL Error: " + std::string(SDL_GetError()));
	}

	if (color->a < 255) {
		if (SDL_SetTextureBlendMode(sprite->texture, DEFAULT_BLEND_MODE) < 0) {
			Log::s()->logError("Unable to set the texture blend mode! SDL Error: " + std::string(SDL_GetError()));
		}

		if (SDL_SetTextureAlphaMod(sprite->texture, color->a) < 0) {
			Log::s()->logError("Unable to set the texture alpha mod! SDL Error: " + std::string(SDL_GetError()));
		}
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
	if (SDL_RenderCopyEx(renderer, sprite->texture, clip, &positionAndSize, sprite->angle, sprite->getAnchor(), sprite->flip) < 0) {
		Log::s()->logError("An error occured when rendering a sprite! SDL Error: " + std::string(SDL_GetError()));
	}

	//Restore color mod and alpha mod
	if (SDL_SetTextureColorMod(sprite->texture, DEFAULT_COLOR_SCHEME.r, DEFAULT_COLOR_SCHEME.g, DEFAULT_COLOR_SCHEME.b) < 0) {
		Log::s()->logError("Unable to set the texture color mod! SDL Error: " + std::string(SDL_GetError()));
	}

	if (color->a < 255) {
		if (SDL_SetTextureBlendMode(sprite->texture, SDL_BLENDMODE_BLEND) < 0) {
			Log::s()->logError("Unable to set the texture blend mode! SDL Error: " + std::string(SDL_GetError()));
		}

		if (SDL_SetTextureAlphaMod(sprite->texture, DEFAULT_COLOR_SCHEME.a) < 0) {
			Log::s()->logError("Unable to set the texture alpha mod! SDL Error: " + std::string(SDL_GetError()));
		}
	}
}

void Screen::renderFilledSquare(const SDL_Rect* fillRect, const Colors color) const {
	if (SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0) {
		Log::s()->logError("An error occured when setting the rendering color! SDL Error: " + std::string(SDL_GetError()));
	}

	if (SDL_RenderFillRect(renderer, fillRect) < 0) {
		Log::s()->logError("An error occured when rendering a filled rect! SDL Error: " + std::string(SDL_GetError()));
	}

	if (SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a) < 0) {
		Log::s()->logError("An error occured when resetting the rendering color to the screens background color! SDL Error: " + std::string(SDL_GetError()));
	}
}

void Screen::renderDrawnSquare(const SDL_Rect* drawRect, const Colors color) const {
	if (SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0) {
		Log::s()->logError("An error occured when setting the rendering color! SDL Error: " + std::string(SDL_GetError()));
	}

	if (SDL_RenderDrawRect(renderer, drawRect) < 0) {
		Log::s()->logError("An error occured when rendering an empty rect! SDL Error: " + std::string(SDL_GetError()));
	}

	if (SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a) < 0) {
		Log::s()->logError("An error occured when resetting the rendering color to the screens background color! SDL Error: " + std::string(SDL_GetError()));
	}
}

void Screen::renderDot(const SDL_Point dot, const SDL_Color* color) const {
	if (SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a) < 0) {
		Log::s()->logError("An error occured when setting the rendering color! SDL Error: " + std::string(SDL_GetError()));
	}

	if (SDL_RenderDrawPoint(renderer, dot.x, dot.y) < 0) {
		Log::s()->logError("An error occured when rendering a dot! SDL Error: " + std::string(SDL_GetError()));
	}

	if (SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a) < 0) {
		Log::s()->logError("An error occured when resetting the rendering color to the screens background color! SDL Error: " + std::string(SDL_GetError()));
	}
}

void Screen::renderGeometryDot(const GeometryDot* dot) const {
	renderDot({ (int) dot->getPosition()->x, (int) dot->getPosition()->y }, dot->getColorMod());
}

void Screen::renderLine(const SDL_Point lineOrigin, const SDL_Point lineDestination, const SDL_Color* color) const {
	if (SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a) < 0) {
		Log::s()->logError("An error occured when setting the rendering color! SDL Error: " + std::string(SDL_GetError()));
	}

	if (SDL_RenderDrawLine(renderer, lineOrigin.x, lineOrigin.y, lineDestination.x, lineDestination.y) < 0) {
		Log::s()->logError("An error occured when rendering a line! SDL Error: " + std::string(SDL_GetError()));
	}

	if (SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a) < 0) {
		Log::s()->logError("An error occured when resetting the rendering color to the screens background color! SDL Error: " + std::string(SDL_GetError()));
	}
}

void Screen::renderGeometryLine(const GeometryLine* line) const {
	renderLine({ (int) line->getPositionOrigin()->x, (int) line->getPositionOrigin()->y }, { (int) line->getPositionDestination()->x, (int) line->getPositionDestination()->y }, line->getColorMod());
}

void Screen::setViewport(const SDL_Rect* viewport) {
	if (SDL_RenderSetViewport(renderer, viewport) < 0) {
		Log::s()->logError("An error occured when setting the viewport! SDL Error: " + std::string(SDL_GetError()));
	}

	this->viewportWidth = viewport->w;
	this->viewportHeight = viewport->h;
}

void Screen::restoreNormalViewport() {
	if (SDL_RenderSetViewport(renderer, &normalViewport) < 0) {
		Log::s()->logError("An error occured when setting the viewport! SDL Error: " + std::string(SDL_GetError()));
	}

	this->viewportWidth = width;
	this->viewportHeight = height;
}