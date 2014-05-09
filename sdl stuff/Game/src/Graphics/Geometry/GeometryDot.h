#ifndef GEOMETRYDOT_H
#define GEOMETRYDOT_H

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

//SDL
#include <SDL.h>

//C++
#include <stdio.h>
#include <string>

//OWN
#include "GeometryObject.h"

class Screen;

class GeometryDot : public GeometryObject {
	/*************** Variables ***************/
private:

protected:

public:

	/*************** Contructors & Destructors ***************/
public:
	GeometryDot();
	GeometryDot(const std::string name);
	virtual ~GeometryDot();

	/*************** Methods ***************/
private:

protected:
	//Resets all variables to default values
	virtual void			resetToDefaultValues();

public:
	//Update the dot
	virtual void			update();

	//Render the dot
	virtual void			render(Screen* screen);

	//Loads the dot
	virtual bool			load(float x, float y, Uint8 rMod = 255, Uint8 gMod = 255, Uint8 bMod = 255, Uint8 alpha = 255);

	//Loads the dot
	virtual bool			load(float x, float y, Colors color = Colors::White);

	//Sets the position with the given values
	virtual void			setAnchor(const float x, const float y);
};

#endif
