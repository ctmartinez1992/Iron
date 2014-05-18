#ifndef SCREEN_H
#define SCREEN_H

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

//SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//C++
#include <stdio.h>
#include <string>
#include <vector>

//OWN
#include "Colors.h"
#include "Fonts.h"
#include "SpriteSheet.h"
#include "../Util/Log.h"

class GameObject;
//class TTFText;
class Sprite;
class GeometryDot;
class GeometryLine;
class GeometryTriangle;

class Screen {
	/*************** Variables ***************/
	private:
		//The canvas.
		SDL_Window*				window;

		//The name of the window.
		const char*				screenTitle;

		//Controls if the Screen class was initiated.
		bool					init;

	protected:
		/*!
		\brief Global alternative vertex array that is used when a certain parameters is NULL, see renderFilledPolygon
		*/
		static int*				PRIMITIVE_POLYGON_INTEGERS;

		/*!
		\brief Flag indicating the amount of integers allocated, see renderFilledPolygon
		*/
		static int				PRIMITIVE_POLYGON_INTEGERS_COUNT;

	public:
		//Singleton.
		static Screen*			_instance;

		//Default Blend Mode, use to restore values
		static SDL_BlendMode	DEFAULT_BLEND_MODE;

		//Default Color Scheme, use to restore values
		static SDL_Color		DEFAULT_COLOR_SCHEME;

		//The window renderer.
		SDL_Renderer*			renderer;

		//Standard applied viewport
		SDL_Rect				normalViewport;

		//The resolution of the screen and other pre-computed resolutions.
		Uint16					width;
		Uint16					height;
		Uint16					widthHalf;
		Uint16					heightHalf;
		Uint16					widthThird;
		Uint16					heightThird;
		Uint16					widthFourth;
		Uint16					heightFourth;

		//The current viewport width and height
		Uint16					viewportWidth;
		Uint16					viewportHeight;

		//Background color
		Colors					bg;


	/*************** Contructors & Destructors ***************/
	public:
		Screen();
		Screen(const char* screenTitle, Uint16 width, Uint16 height);
		~Screen();

	/*************** Methods ***************/
	private:
		//Sets the color mod and the blend mode for the renderer
		int 					setColorAndBlendForRenderer(const SDL_Color* color, const SDL_BlendMode blend) const;

		//Sets the color mod and the blend mode for the renderer
		int 					setColorAndBlendForTexture(SDL_Texture* texture, const SDL_Color* color, const SDL_BlendMode blend) const;

	protected:

	public:
		//Obtain an instance of the Screen class.
		static Screen*			getInstance();

		//Initializes the class.
		bool					initScreen();

		//Clears the entire screen.
		void					clearScreen();

		//Flush the screen to render everything.
		void					updateScreen();

		//Loads and returns a SDL_Texture pointer.
		SDL_Texture*			loadTexture(const std::string path);

		//Loads the text and returns a SDL_Texture pointer to the text texture.
		//SDL_Texture*			loadTextTexture(const std::string text, const Fonts font);

		//Sets a viewport for the screen
		void					setViewport(const SDL_Rect* viewport);

		//Sets a viewport for the screen
		void					restoreNormalViewport();
		
		/******************************************************************************/
		/******************************  TEXT RENDERING  ******************************/
		/******************************************************************************/
		//Renders a TTFText (see class) to the screen
		//int						renderTTFText(const TTFText* text) const;

		/********************************************************************************/
		/******************************  SPRITE RENDERING  ******************************/
		/********************************************************************************/
		//Renders a Sprite (see class) to the screen
		int						renderSprite(const Sprite* sprite) const;

		/***********************************************************************************/
		/******************************  PRIMITIVE RENDERING  ******************************/
		/***********************************************************************************/

		//Renders a point to the screen.
		int						renderDot(const int x, const int y, const SDL_Color* color) const;

		//Renders a point to the screen.
		int						renderDot(const SDL_Point dot, const SDL_Color* color) const;

		//Renders a GeometryDot object to the screen.
		int						renderGeometryDot(const GeometryDot* dot) const;

		//Renders a point to the screen.
		int						renderLine(const int xO, const int yO, const int xD, const int yD, const SDL_Color* color) const;

		//Renders a point to the screen.
		int						renderLine(const SDL_Point lineOrigin, const SDL_Point lineDestination, const SDL_Color* color) const;

		//Renders a GeometryDot object to the screen.
		int						renderGeometryLine(const GeometryLine* line) const;

		//Renders the outline of a triangle to the screen.
		int						renderDrawnTriangle(const SDL_Point point1, const SDL_Point point2, const SDL_Point point3, const SDL_Color* color) const;

		//Renders a filled triangle to the screen.
		int						renderFilledTriangle(const SDL_Point point1, const SDL_Point point2, const SDL_Point point3, const SDL_Color* color) const;

		//Renders a GeometryTriangle object to the screen.
		int						renderGeometryTriangle(const GeometryTriangle* triangle) const;

		//Renders a border-only square to the screen.
		//void					renderDrawnSquare(const SDL_Rect* drawRect, const Colors color) const;

		//Renders a filled square to the screen.
		//void					renderFilledSquare(const SDL_Rect* fillRect, const Colors color) const;

		/*!
		\brief Render a (colored with alpha) drawn polygon to the screen
		\param renderer The renderer to draw on
		\param xArray Vertex array containing X coordinates of the points of the polygon
		\param yArray Vertex array containing Y coordinates of the points of the polygon
		\param nPoints Number of points in the array. Minimum number is 3
		\param color the color for the polygon
		\returns Returns 0 on success, -1 on failure
		*/
		int						renderDrawnPolygon(SDL_Renderer* renderer, const Sint16* xArray, const Sint16* yArray, int nPoints, const SDL_Color* color) const;

		/*!
		\brief Render a (colored with alpha) filled polygon to the screen
		\param renderer The renderer to draw on
		\param vx Vertex array containing X coordinates of the points of the filled polygon
		\param vy Vertex array containing Y coordinates of the points of the filled polygon
		\param n Number of points in the vertex array. Minimum number is 3
		\param r The red value of the filled polygon to draw
		\param g The green value of the filled polygon to draw
		\param b The blue value of the filled polygon to draw
		\param a The alpha value of the filled polygon to draw
		\param polyInts (OPTIONAL) - Preallocated, temporary vertex array used for sorting vertices. Required for multithreaded operation; set to NULL otherwise. Required for multithreading
		\param polyAllocated (OPTIONAL) - Flag indicating if temporary vertex array was allocated. Required for multithreaded operation; set to NULL otherwise. Required for multithreading
		\returns Returns 0 on success, -1 on failure
		TODO: change mallocs and reallocs and the cached variables to std::vector
		*/
		int						renderFilledPolygon(SDL_Renderer* renderer, const Sint16* vx, const Sint16* vy, int n, const SDL_Color* color, int** polyInts = NULL, int* polyAllocated = NULL) const;
};

#endif