#ifndef IRON_DEMO_APP_H_
#define IRON_DEMO_APP_H_

#include <glew.h>
#include <gl/glut.h>
#include <Iron.h>

/*! \brief Temporary basic graphics application that allows to render some text and some shapes.
*
*  In the future, this will be replaced by the engine own "app" states.
*/
class App {
	/****************************** Variables ******************************/
private:

protected:
	int					width;			/*!< Width of the screen. */

	int					height;			/*!< Height of the screen. */

public:


	/****************************** Contructors & Destructors ******************************/
public:

private:

	/****************************** Virtual Methods ******************************/
private:

protected:

public:
	/**
	* Graphical initialization.
	*/
	virtual void init();

	/**
	* Destroys stuff.
	*/
	virtual void destroy();

	/**
	* Update glut.
	*/
	virtual void update();

	/**
	* Render default line.
	*/
	virtual void render();

	/**
	* Virtual function for mouse clicking behaviour.
	*
	* @param state The current state of the mouse button.
	* @param button The pressed mouse button
	* @param x The x position of the mouse at which the state happened.
	* @param y The y position of the mouse at which the state happened.
	*/
	virtual void mouseClick(const int state, const int button, const int x, const int y);

	/**
	* Virtual function for mouse drag behaviour.
	*
	* @param x The new x mouse position.
	* @param y The new y mouse position.
	*/
	virtual void mouseDrag(const int x, const int y);

	/**
	* Virtual function for keyboard behaviour.
	*
	* @param key The pressed key.
	*/
	virtual void keys(const unsigned char key);

	/**
	* Resizes the screen to the given parameters.
	*/
	virtual void resize(const int width, const int height);

	/**
	* Sets the default glut camera view.
	*/
	virtual void view();

	/**
	* Returns the title of the application.
	*
	* @return The title of the application.
	*/
	virtual const std::string title();

	/****************************** Methods ******************************/
private:

protected:

public:
	/**
	* Renders the given text with the given font at the given position.
	*
	* @param x The x position of the text.
	* @param y The y position of the text.
	* @param text A pointer to the content of the text.
	* @param font The font for the text. Must be a standard GLUT font.
	*/
	void renderText(float x, float y, const char* text, void* font = NULL);

	/****************************** Operators Overloading ******************************/
private:

protected:

public:

};

#endif