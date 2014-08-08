#ifndef FONTSTRUCT_H
#define FONTSTRUCT_H

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

//SDL
#include <SDL_ttf.h>

//C++
#include <string>

//OWN
#include "../Util/Log.h"
#include "Colors.h"

/*!
\brief Font struct holds the values necessary to control a font
*/
struct Font {
	Font(const std::string id, const std::string path, const Colors* color, const Uint8 size) : font(nullptr), color(), id(id), path(path), size(size)
	{
		//Lose constness, assign the color
		this->color = const_cast<Colors*>(color);

		//Open the font
		font = TTF_OpenFont(path.c_str(), size);
		if (font == NULL) {
			font = nullptr;
			Log::s()->logError("The font with the id [" + id + "] and path [" + path + "] failed to be loaded! TTF Error: " + std::string(TTF_GetError()));
		}

		Log::s()->logDebug("A Font object with the id [" + id + "] and path [" + path + "] was loaded");
	}

	virtual ~Font() {
		TTF_CloseFont(font);
		font = nullptr;

		Log::s()->logDebug("A Font object with the id [" + id + "] and path [" + path + "] was UNloaded");
	}

	/*!
	\brief a TTF_Font variable that holds the loaded font
	*/
	TTF_Font*							font;

	/*!
	\brief The color of the font
	*/
	Colors*								color;

	/*!
	\brief Uniquely identifies the font
	*/
	std::string							id;

	/*!
	\brief The path to the font
	*/
	std::string							path;

	/*!
	\brief The size of the font
	*/
	Uint8								size;
};

#endif