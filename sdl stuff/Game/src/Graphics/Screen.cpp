#define _CRTDBG_MAP_ALLOC
#include "Screen.h"
#include "../General/GameObject.h"
#include "Text/TTFText.h"
#include "Sprite.h"
#include "../Graphics/Geometry/GeometryDot.h"
#include "../Graphics/Geometry/GeometryLine.h"
#include "../Graphics/Geometry/GeometryTriangle.h"

int*				Screen::PRIMITIVE_POLYGON_INTEGERS;
int					Screen::PRIMITIVE_POLYGON_INTEGERS_COUNT = 0;
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
	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;

	Log::s()->logInfo("Screen was destroyed");

	//Invalidade singleton
	_instance = 0;
}

/*!
\brief Internal qsort callback used in renderFilledPolygon
\param a Drawing context
\param b Vertex array of x coordinates
\returns Returns 0 if a == b, <0 if a<b or >0 if a>b
*/
int qsortCompareInt(const void* a, const void* b) {
	return ((*(const int*)a) - (*(const int*)b));
}

int Screen::setColorAndBlendForRenderer(const SDL_Color* color, const SDL_BlendMode blend) const {
	if (SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a) < 0) {
		Log::s()->logError("An error occured when setting the rendering color! SDL Error: " + std::string(SDL_GetError()));
		return -1;
	}

	if (color->a < 255) {
		if (SDL_SetRenderDrawBlendMode(renderer, blend) < 0) {
			Log::s()->logError("Unable to set the renderer blend mode! SDL Error: " + std::string(SDL_GetError()));
			return -1;
		}
	}

	return 0;
}

int Screen::setColorAndBlendForTexture(SDL_Texture* texture, const SDL_Color* color, const SDL_BlendMode blend) const {
	if (SDL_SetTextureColorMod(texture, color->r, color->g, color->b) < 0) {
		Log::s()->logError("Unable to set the texture color mod! SDL Error: " + std::string(SDL_GetError()));
		return -1;
	}

	if (color->a < 255) {
		if (SDL_SetTextureBlendMode(texture, blend) < 0) {
			Log::s()->logError("Unable to set the texture blend mode! SDL Error: " + std::string(SDL_GetError()));
			return -1;
		}

		if (SDL_SetTextureAlphaMod(texture, color->a) < 0) {
			Log::s()->logError("Unable to set the texture alpha mod! SDL Error: " + std::string(SDL_GetError()));
			return -1;
		}
	}

	return 0;
}

Screen* Screen::getInstance() {
   if (!_instance) {
      _instance = new Screen;
   }
   return _instance;
}

bool Screen::initScreen() {
	//Initialization flag
	bool success = true;

	Log::s()->logInfo("Screen is being initialized...");

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		success = false;
	} else {
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			Log::s()->logWarning("Linear texture filtering not enabled! SDL Error: " + std::string(SDL_GetError()));
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
				if (SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF) < 0) {
					Log::s()->logError("An error occured when setting the rendering color! SDL Error: " + std::string(SDL_GetError()));
					success = false;
				}

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					Log::s()->logError("SDL_image could not initialize! SDL_image Error: " + std::string(IMG_GetError()));
					success = false;
				}

				//Initialized TTF loading
				//Screen does not load TTF, it is done in Fonts class due to timing issues
			}
		}
	}

	if (success) {
		Log::s()->logInfo("Screen was initialized successfully");
	}

	return success;
}

void Screen::clearScreen() {
	SDL_Color bgColor = { bg.r, bg.g, bg.b, bg.a };
	setColorAndBlendForRenderer(&bgColor, SDL_BLENDMODE_BLEND);
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
	} else {
		//Create texture from surface pixels.
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == nullptr) {
			Log::s()->logError("Unable to create texture from " + path + "! SDL Error: " + std::string(SDL_GetError()));
		}

		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

SDL_Texture* Screen::loadTextTexture(const std::string text, Font* font, int* width, int* height) {
	SDL_Texture* newTexture = nullptr;

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font->font, text.c_str(), font->color->toSDLColor());
	if (textSurface == NULL) {
		Log::s()->logError("Unable to render text surface! (at loadTextTexture) SDL_ttf Error: " + std::string(TTF_GetError()));
	} else {
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (newTexture == NULL) {
			Log::s()->logError("Unable to create texture from text texture! SDL Error: " + std::string(SDL_GetError()));
		} else {
			//Get image dimensions
			*width = textSurface->w;
			*height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return newTexture;
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

int Screen::renderTTFText(const TTFText* text) const {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { 10, 10, text->width, text->height };

	//Render to screen
	if (SDL_RenderCopyEx(renderer, text->texture, NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE) < 0) {
		Log::s()->logError("An error occured when rendering a TTFText! SDL Error: " + std::string(SDL_GetError()));
		return -1;
	}

	return 0;
}

int	Screen::renderSprite(const Sprite* sprite) const {
	short result = 0;

	//Create SDL_Rect with position and dimensions and assign color mod and alpha mod
	SDL_Rect positionAndSize = { (int) sprite->getPosition()->x, (int) sprite->getPosition()->y, sprite->getSpriteClip()->w, sprite->getSpriteClip()->h };

	//Set the color mod, alpha mod and blend mode for the given texture
	result = setColorAndBlendForTexture(sprite->texture, sprite->getColorMod(), SDL_BLENDMODE_BLEND);

	//Obtain clip
	SDL_Rect* clip = (sprite->useClip) ? sprite->getSpriteClip() : nullptr;

	//If it's animated, clip it properly
	if (sprite->useAnimation) {
		if (sprite->animations->currentAnimation != nullptr) {
			clip->x = (sprite->animations->currentAnimation->getCurrentFrame() % sprite->sheet->getNRowsAndColumns()) * clip->w;
			clip->y = (sprite->animations->currentAnimation->getCurrentFrame() / sprite->sheet->getNRowsAndColumns()) * clip->h;
		} else {
			Log::s()->logWarning("Sprite with the name (" + sprite->name + ") is set to use animations but has no current animation associated");
		}
	}

	//Render
	if (SDL_RenderCopyEx(renderer, sprite->texture, clip, &positionAndSize, sprite->angle, sprite->getAnchor(), sprite->flip) < 0) {
		Log::s()->logError("An error occured when rendering a sprite! SDL Error: " + std::string(SDL_GetError()));
		result = -1;
	}

	return result;
}

int	Screen::renderDot(const int x, const int y, const SDL_Color* color) const {
	short result = 0;

	//Set the color mod and blend mode for the given renderer
	result = setColorAndBlendForRenderer(color, SDL_BLENDMODE_BLEND);

	//Render the dot
	if (SDL_RenderDrawPoint(renderer, x, y) < 0) {
		Log::s()->logError("An error occured when rendering a dot! SDL Error: " + std::string(SDL_GetError()));
		return -1;
	}

	return result;
}

int	Screen::renderDot(const SDL_Point dot, const SDL_Color* color) const {
	return renderDot(dot.x, dot.y, color);
}

int	Screen::renderGeometryDot(const GeometryDot* dot) const {
	//Call the renderDot function and pass the correct parameters
	if (dot != nullptr) {
		return renderDot({ (int)dot->getPosition()->x, (int)dot->getPosition()->y }, dot->getColorMod());
	}

	Log::s()->logWarning("RenderGeometryDot tried to render a dot but it failed because the GeometryDot object was NULL");
	return -1;
}

int	Screen::renderLine(const int xO, const int yO, const int xD, const int yD, const SDL_Color* color) const {
	short result = 0;

	//Set the color mod and blend mode for the given renderer
	result = setColorAndBlendForRenderer(color, SDL_BLENDMODE_BLEND);

	//Render the line
	if (SDL_RenderDrawLine(renderer, xO, yO, xD, yD) < 0) {
		Log::s()->logError("An error occured when rendering a line! SDL Error: " + std::string(SDL_GetError()));
		return -1;
	}

	return result;
}

int	Screen::renderLine(const SDL_Point lineOrigin, const SDL_Point lineDestination, const SDL_Color* color) const {
	return renderLine(lineOrigin.x, lineOrigin.y, lineDestination.x, lineDestination.y, color);
}

int	Screen::renderGeometryLine(const GeometryLine* line) const {
	//Call the renderLine function and pass the correct parameters
	if (line != nullptr) {
		return renderLine({ (int)line->getPositionOrigin()->x, (int)line->getPositionOrigin()->y }, { (int)line->getPositionDestination()->x, (int)line->getPositionDestination()->y }, line->getColorMod());
	}

	Log::s()->logWarning("RenderGeometryLine tried to render a line but it failed because the GeometryLine object was NULL");
	return -1;
}

int Screen::renderDrawnTriangle(const SDL_Point point1, const SDL_Point point2, const SDL_Point point3, const SDL_Color* color) const {
	//Create the X and Y array with the points
	Sint16 vx[3];
	Sint16 vy[3];

	//Assign them
	vx[0] = point1.x;
	vx[1] = point2.x;
	vx[2] = point3.x;
	vy[0] = point1.y;
	vy[1] = point2.y;
	vy[2] = point3.y;

	//Call the renderDrawnPolygon function with the correct values
	return renderDrawnPolygon(renderer, vx, vy, 3, color);
}

int Screen::renderFilledTriangle(const SDL_Point point1, const SDL_Point point2, const SDL_Point point3, const SDL_Color* color) const {
	//Create the X and Y array with the points
	Sint16 vx[3];
	Sint16 vy[3];

	//Assign them
	vx[0] = point1.x;
	vx[1] = point2.x;
	vx[2] = point3.x;
	vy[0] = point1.y;
	vy[1] = point2.y;
	vy[2] = point3.y;

	//Call the renderFilledPolygon function with the correct values
	return renderFilledPolygon(renderer, vx, vy, 3, color);
}

int	Screen::renderGeometryTriangle(const GeometryTriangle* triangle) const {
	//Call the renderDrawnTriangle or renderFilledTriangle accordingly and pass the correct parameters
	if (triangle != nullptr) {
		if (triangle->filled) {
			return renderFilledTriangle({ (int)triangle->getPosition1()->x, (int)triangle->getPosition1()->y },
										{ (int)triangle->getPosition2()->x, (int)triangle->getPosition2()->y },
										{ (int)triangle->getPosition3()->x, (int)triangle->getPosition3()->y }, triangle->getColorMod());
		} else {
			return renderDrawnTriangle({ (int)triangle->getPosition1()->x, (int)triangle->getPosition1()->y },
									   { (int)triangle->getPosition2()->x, (int)triangle->getPosition2()->y },
									   { (int)triangle->getPosition3()->x, (int)triangle->getPosition3()->y }, triangle->getColorMod());
		}
	}

	Log::s()->logWarning("RenderGeometryTriangle tried to render a triangle but it failed because the Geometrytriangle object was NULL");
	return -1;
}

//void Screen::renderDrawnSquare(const SDL_Rect* drawRect, const Colors color) const {
//	if (SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0) {
//		Log::s()->logError("An error occured when setting the rendering color! SDL Error: " + std::string(SDL_GetError()));
//	}
//
//	if (color->a < 255) {
//		if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) < 0) {
//			Log::s()->logError("Unable to set the renderer blend mode! SDL Error: " + std::string(SDL_GetError()));
//		}
//	}
//
//	if (SDL_RenderDrawRect(renderer, drawRect) < 0) {
//		Log::s()->logError("An error occured when rendering an empty rect! SDL Error: " + std::string(SDL_GetError()));
//	}
//
//	if (color->a < 255) {
//		if (SDL_SetRenderDrawBlendMode(renderer, DEFAULT_BLEND_MODE) < 0) {
//			Log::s()->logError("Unable to set the renderer blend mode! SDL Error: " + std::string(SDL_GetError()));
//		}
//	}
//
//	if (SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a) < 0) {
//		Log::s()->logError("An error occured when resetting the rendering color to the screens background color! SDL Error: " + std::string(SDL_GetError()));
//	}
//}
//
//void Screen::renderFilledSquare(const SDL_Rect* fillRect, const Colors color) const {
//	if (SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0) {
//		Log::s()->logError("An error occured when setting the rendering color! SDL Error: " + std::string(SDL_GetError()));
//	}
//
//	if (color->a < 255) {
//		if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) < 0) {
//			Log::s()->logError("Unable to set the renderer blend mode! SDL Error: " + std::string(SDL_GetError()));
//		}
//	}
//
//	if (SDL_RenderFillRect(renderer, fillRect) < 0) {
//		Log::s()->logError("An error occured when rendering a filled rect! SDL Error: " + std::string(SDL_GetError()));
//	}
//
//	if (color->a < 255) {
//		if (SDL_SetRenderDrawBlendMode(renderer, DEFAULT_BLEND_MODE) < 0) {
//			Log::s()->logError("Unable to set the renderer blend mode! SDL Error: " + std::string(SDL_GetError()));
//		}
//	}
//
//	if (SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a) < 0) {
//		Log::s()->logError("An error occured when resetting the rendering color to the screens background color! SDL Error: " + std::string(SDL_GetError()));
//	}
//}

int Screen::renderDrawnPolygon(SDL_Renderer* renderer, const Sint16* xArray, const Sint16* yArray, int nPoints, const SDL_Color* color) const {
	//Temporary variables
	short result = 0;
	int extraPoint = 0;
	std::vector<SDL_Point> points;

	//Check arrays and if nPoints is above or equal to 3, because polygons need at least 3 points
	if (xArray == NULL) {
		Log::s()->logWarning("renderDrawnPolygon function received an empty X array");
		return -1;
	}

	if (yArray == NULL) {
		Log::s()->logWarning("renderDrawnPolygon function received an empty Y array");
		return -1;
	}

	if (nPoints < 3) {
		Log::s()->logWarning("renderDrawnPolygon function received an invalid nPoints value, it must be above 3 but, it was equal to " + (nPoints));
		return -1;
	}

	//Create the array of points, a temporary array that holds all points that are going to be rendered
	extraPoint = nPoints + 1;
	points.reserve(extraPoint);
	//points = new SDL_Point[extraPoint]();

	//Fill the array
	for (int i = 0; i < nPoints; i++) {
		points.push_back({ xArray[i], yArray[i] });
	}

	//The extra point is used to close the polygon
	points.push_back({ xArray[0], yArray[0] });

	result = setColorAndBlendForRenderer(color, SDL_BLENDMODE_BLEND);

	//Render all the points
	if (SDL_RenderDrawLines(renderer, &points[0], extraPoint) < 0) {
		Log::s()->logError("An error occured when rendering the lines of a polygon! SDL Error: " + std::string(SDL_GetError()));
		return -1;
	}

	return result;
}

//TODO Need to be changed to use std vector or something better then allocs
int Screen::renderFilledPolygon(SDL_Renderer* renderer, const Sint16* vx, const Sint16* vy, int nPoints, const SDL_Color* color, int** polyInts, int* polyAllocated) const {
	//Result of the function
	short result;
	
	//Check arrays and if nPoints is above or equal to 3, because polygons need at least 3 points
	if (vx == NULL) {
		return -1;
	}

	if (vy == NULL) {
		return -1;
	}

	if (nPoints < 3) {
		return -1;
	}

	//Cached variables for the polygon build
	int cachedPolygonIntsCount = 0;
	int *cachedPolygonInts = NULL;
	int *cachedPolygonIntsNew = NULL;

	//Map the cached polygon values to use the global vlaues or the passed local values
	if (polyInts == NULL || polyAllocated == NULL) {
		cachedPolygonInts = PRIMITIVE_POLYGON_INTEGERS;
		cachedPolygonIntsCount = PRIMITIVE_POLYGON_INTEGERS_COUNT;
	} else {
		cachedPolygonInts = *polyInts;
		cachedPolygonIntsCount = *polyAllocated;
	}

	//If it's the first time, then it goes in here
	if (!cachedPolygonInts) {
		cachedPolygonInts = (int*) malloc(sizeof(int)* nPoints);
		cachedPolygonIntsCount = nPoints;
	} else {
		//Allocate the array if a smaller one is needed
		if (cachedPolygonIntsCount < nPoints) {
			cachedPolygonIntsNew = (int*)realloc(cachedPolygonInts, sizeof(int)* nPoints);
			if (!cachedPolygonIntsNew) {
				cachedPolygonIntsCount = 0;
			} else {
				cachedPolygonInts = cachedPolygonIntsNew;
				cachedPolygonIntsCount = nPoints;
			}
		}
	}

	//Recheck the array, leave if it's NULL
	if (cachedPolygonInts == NULL) {
		Log::s()->logWarning("Function renderFilledPolygon failed to update internal cached variables and cannot render the polygon");
		return -1;
	}

	//Update the cached variables
	if (polyInts == NULL || polyAllocated == NULL) {
		PRIMITIVE_POLYGON_INTEGERS = cachedPolygonInts;
		PRIMITIVE_POLYGON_INTEGERS_COUNT = cachedPolygonIntsCount;
	} else {
		*polyInts = cachedPolygonInts;
		*polyAllocated = cachedPolygonIntsCount;
	}

	//Calculate the lowest and the highest y value (minimum and maximum)
	int minY = vy[0];
	int maxY = vy[0];
	for (int i = 1; (i < nPoints); i++) {
		if (vy[i] < minY) {
			minY = vy[i];
		} else if (vy[i] > maxY) {
			maxY = vy[i];
		}
	}

	//More temporary variables for the lines calculation
	int xO;
	int yO;
	int xD;
	int yD;
	int xDrawO;
	int xDrawD;

	int ints;
	int index1;
	int index2;

	int maxLimitInt = std::numeric_limits<Sint16>::max() + 1;
	int maxLimitUnsignedInt = std::numeric_limits<Uint16>::max() + 1;

	//Draw the polygon line by line
	result = 0;
	for (int y = minY; y <= maxY; y++) {
		ints = 0;
		for (int i = 0; (i < nPoints); i++) {
			//Stops from getting a negative value
			if (!i) {
				index1 = nPoints - 1;
				index2 = 0;
			} else {
				index1 = i - 1;
				index2 = i;
			}

			yO = vy[index1];
			yD = vy[index2];

			//Decide x values based on y values
			if (yO < yD) {
				xO = vx[index1];
				xD = vx[index2];
			} else if (yO > yD) {
				yD = vy[index1];
				yO = vy[index2];
				xD = vx[index1];
				xO = vx[index2];
			} else {
				continue;
			}

			if (((y >= yO) && (y < yD)) || ((y == maxY) && (y > yO) && (y <= yD))) {
				cachedPolygonInts[ints++] = ((maxLimitUnsignedInt * (y - yO)) / (yD - yO)) * (xD - xO) + (maxLimitUnsignedInt * xO);
			}
		}

		//Quick Sort the polygon values
		qsort(cachedPolygonInts, ints, sizeof(int), qsortCompareInt);

		for (int i = 0; i < ints; i += 2) {
			xDrawO = cachedPolygonInts[i] + 1;
			xDrawO = (xDrawO >> 16) + ((xDrawO & maxLimitInt) >> 15);
			xDrawD = cachedPolygonInts[i + 1] - 1;
			xDrawD = (xDrawD >> 16) + ((xDrawD & maxLimitInt) >> 15);
			result |= renderLine(xDrawO, y, xDrawD, y, color);
		}
	}

	//Deallocate cached values
	if (!cachedPolygonInts) {
		free(cachedPolygonInts);
		cachedPolygonInts = NULL;
	}

	return (result);
}