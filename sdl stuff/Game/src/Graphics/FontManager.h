#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

//SDL
#include <SDL_ttf.h>

//C++
#include <string>
#include <map>

//OWN
#include "../Util/Log.h"v
#include "Screen.h"
#include "Colors.h"

/*!
\brief Font struct holds the values necessary to control a font
*/
struct Font {

	Font(const std::string id, const std::string path, const Colors* color, const Uint8 size) : font(nullptr), color(), id(id), path(path), size(size), width(0), height(0)
	{
		//Lose constness, assign the color
		this->color = const_cast<Colors*>(color); 
		
		//Open the font
		font = TTF_OpenFont(path.c_str(), size);
		if (font == NULL) {
			font = nullptr;
			Log::s()->logError("The font with the id [" + id + "] and path [" + path + "] failed to be loaded! TTF Error: " + std::string(TTF_GetError()));
		}
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

	/*!
	\brief Width and height of the font text
	*/
	Uint16								width;
	Uint16								height;
};

/*!
\brief FontManager manages all the fonts in the game, all fonts are represented by the Font struct. Custom fonts must be added to the map of fonts in order for them to be used.
*/
class FontManager {
	/*************** Variables ***************/
private:
	/*!
	\brief Pointer to the unique logger
	*/
	static FontManager*					_s;

	/*!
	\brief Pointer to the screen class
	*/
	Screen*								screen;

protected:

public:
	std::map<std::string, Font*>		fonts;

	/*!
	\brief Currently used font for text rendering
	*/
	Font*								currentFont;

	/*!
	\brief Amount of added fonts
	*/
	Uint16								nFonts;

	/*************** Contructors & Destructors ***************/
public:
	FontManager();
	FontManager(Screen* screen);
	virtual ~FontManager();

	/*************** Methods ***************/
private:
	//Don't implement
	FontManager&						operator=(const FontManager&) { return *this; };

	//Don't implement
	FontManager(FontManager const&);

protected:

public:
	/*!
	\brief singleton get
	*/
	static FontManager*					s();

	/*!
	\brief Creates and adds a font to the map
	\param id Identifies the font loaded in the map, used to get the font
	\param path The path to the font's ttf file
	\param color Pointer to a Colors static object, will render the text with the given color
	\param size The size of the font
	*/
	int									addFont(const std::string id, const std::string path, const Colors* color = &Colors::Black, const Uint8 size = 20);
};
#endif