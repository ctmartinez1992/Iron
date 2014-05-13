#ifndef GEOMETRYLINE_H
#define GEOMETRYLINE_H

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

class GeometryLine : public GeometryObject {
	/*************** Variables ***************/
private:
	//The destination posiiton of the line
	Vector2*				positionDestination;

protected:

public:

	/*************** Contructors & Destructors ***************/
public:
	GeometryLine();
	GeometryLine(const std::string name);
	virtual ~GeometryLine();

	/*************** Methods ***************/
private:

protected:
	//Resets all variables to default values
	virtual void			resetToDefaultValues();

public:
	//Update the line
	virtual void			update();

	//Render the line
	virtual void			render(Screen* screen);

	//Loads the line, x, y are the origin coordinate and x2, y2 are the destination coordinates
	virtual bool			load(float x, float y, float x2, float y2, Uint8 rMod = 255, Uint8 gMod = 255, Uint8 bMod = 255, Uint8 alpha = 255);

	//Loads the line
	virtual bool			load(float x, float y, float x2, float y2, Colors color = Colors::White);

	//Sets the position with the given values
	virtual void			setAnchor(const float x, const float y);

	//Sets the origin and destination position with the given values
	void					setPositionAll(const float xO, const float yO, const float xD, const float yD);

	//Sets the origin position with the given values
	void					setPositionOrigin(const float x, const float y);

	//Gets the origin position
	Vector2*				getPositionOrigin() const;

	//Sets the destination position with the given values
	void					setPositionDestination(const float x, const float y);

	//Gets the destination position
	Vector2*				getPositionDestination() const;
};

#endif
