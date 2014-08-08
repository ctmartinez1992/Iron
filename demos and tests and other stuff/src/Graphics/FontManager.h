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
#include "../Util/Log.h"
#include "Font.h"
#include "Screen.h"
#include "Colors.h"

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
	/*!
	\brief All of the fonts are stored in here, the key is the identifier and the value is the font
	*/
	std::map<std::string, struct Font*>	fonts;

	/*!
	\brief Currently used font for text rendering
	*/
	struct Font*						currentFont;

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
	\return Returns 0 if successful, -1 is there was an error
	*/
	int									addFont(const std::string id, const std::string path, const Colors* color = &Colors::Black, const Uint8 size = 20);

	/*!
	\brief Sets the currentFont variable to an existent font in the fonts map
	\param id Identifies the font that is going to be used
	\return Returns 0 if font exists, -1 is the font does not exist
	*/
	int									useFont(const std::string id);

	/*!
	\brief Closes the font manager
	*/
	void								close();
};
#endif