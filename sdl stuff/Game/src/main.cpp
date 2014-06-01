//C++
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <string>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

//SDL
#include <SDL.h>
#include <SDL_image.h>

//OWN
#include "General/World.h"
#include "Graphics/Screen.h"
#include "Graphics/FontManager.h"
#include "Graphics/Text/TTFText.h"
#include "Graphics/SpriteSheet.h"
#include "Graphics/Sprite.h"
#include "Graphics/Geometry/GeometryDot.h"
#include "Graphics/Geometry/GeometryLine.h"
#include "Graphics/Geometry/GeometryTriangle.h"
#include "Util\Log.h"

//Organizar os logs, por os INFO nos sitios corretos e por debug nos sitios corretos, ha algumas confusoes

//Screen dimension constants.
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window.
bool init();

//Loads media.
bool loadMedia();

//Updates everything.
void update();

//Renders everything.
void render();

//Frees media and shuts down SDL.
void close();

//TTFText test
TTFText* text = nullptr;

//SpriteSheet test
SpriteSheet* sheet = nullptr;

//Sprite test
Sprite* sprite = nullptr;

//Dots
GeometryDot* dot11 = nullptr;
GeometryDot* dot12 = nullptr;
GeometryDot* dot13 = nullptr;
GeometryDot* dot14 = nullptr;
GeometryDot* dot15 = nullptr;
GeometryDot* dot2 = nullptr;
GeometryDot* dot3 = nullptr;
GeometryDot* dot4 = nullptr;

//Lines
GeometryLine* line1 = nullptr;
GeometryLine* line2 = nullptr;
GeometryLine* line3 = nullptr;
GeometryLine* line4 = nullptr;

//Triangles
GeometryTriangle* tri1 = nullptr;
GeometryTriangle* tri2 = nullptr;

//The screen.
Screen* screen = nullptr;

//The World, handles everything
World* world = nullptr;

bool init() {
	//Checks if the screen was initialized.
	bool successScreen = true;

	//Try to initialize the Screen class.
	if (screen == nullptr) {
		Log::s()->logError("The Screen class can't be initialized... It's nullptr");
		successScreen = false;
	} else {
		successScreen = screen->initScreen();
		screen->bg = Colors::White;
	}

	if(!successScreen) {
		return false;
	}

	//Create the world class
	Log::s()->logInfo("World is being created");
	world = new World(screen);
	Log::s()->logInfo("World was created");

	//Everything went fine.
	return true;
}

bool loadMedia() {
	//Loading success flag.
	bool success = true;

	//Load a font
	FontManager::s()->addFont("ugly", "res/lazy.ttf");
	FontManager::s()->useFont("ugly");

	//Load a TTFText
	text = new TTFText(screen);
	text->load();

	//Load a SpriteSheet
	sheet = new SpriteSheet(screen->renderer);
	sheet->name = "Balls";
	if (!sheet->loadTextureAndClips("res/dots11.png", 200, 200, 4)) {
		printf("Failed to load Sprite Sheet!\n");
		success = false;
	}

	//Add the sprite sheet to the world
	world->addSpriteSheet(sheet);
	
	//Load a sprite from a sheet, clip it and throw some animations in
	sprite = new Sprite(sheet);
	SDL_Rect clip = { 0, 0, sheet->getSpriteWidth(), sheet->getSpriteHeight() };
	sprite->load(200, 200, clip, true, true, 0);
	sprite->animations->addAnimation("cycle", { 0, 1, 2, 3 }, 10, 1);
	sprite->animations->addAnimation("cycle2", { 0, 1, 2, 1, 3, 2, 1 }, 10, 1);
	sprite->animations->play("cycle");
	sprite->name = "Ball";

	//Add the sprite to the world
	world->addSprite(sprite);

	//Load dots
	dot11 = new GeometryDot("dot11");
	dot11->load(20, 20, Colors::Blue);
	dot12 = new GeometryDot("dot12");
	dot12->load(21, 20, Colors::Blue);
	dot13 = new GeometryDot("dot13");
	dot13->load(22, 20, Colors::Blue);
	dot14 = new GeometryDot("dot14");
	dot14->load(23, 20, Colors::Blue);
	dot15 = new GeometryDot("dot15");
	dot15->load(24, 20, Colors::Blue);
	dot2 = new GeometryDot("dot2");
	dot2->load(20, 30, Colors::Red);
	dot3 = new GeometryDot("dot3");
	dot3->load(30, 20, Colors::Green);
	dot4 = new GeometryDot("dot4");
	dot4->load(30, 30, Colors::Black);

	//Add dots to the world
	world->addGeometry(dot11);
	world->addGeometry(dot12);
	world->addGeometry(dot13);
	world->addGeometry(dot14);
	world->addGeometry(dot15);
	world->addGeometry(dot2);
	world->addGeometry(dot3);
	world->addGeometry(dot4);

	//Load lines
	line1 = new GeometryLine("Line1");
	line1->load(60.0f, 60.0f, screen->width - 60.0f, screen->height - 60.0f, Colors::Blue);
	line2 = new GeometryLine("Line2");
	line2->load(screen->width - 60.0f, screen->height - 60.0f, 60.0f, screen->height - 60.0f, Colors::Red);
	line3 = new GeometryLine("Line3");
	line3->load(60.0f, 60.0f, 60.0f, screen->height - 60.0f, Colors::Green);
	line4 = new GeometryLine("Line4");
	line4->load(60.0f, 60.0f, screen->width - 60.0f, 60.0f, Colors::Black);

	//Add lines to the world
	world->addGeometry(line1);
	world->addGeometry(line2);
	world->addGeometry(line3);
	world->addGeometry(line4);

	//Load triangles
	tri1 = new GeometryTriangle("Triangle1");
	tri1->load(700, 200, 750, 300, 650, 300, Colors::Red);
	tri2 = new GeometryTriangle("Triangle2");
	tri2->load(700, 250, 725, 300, 675, 300, Colors::Blue);
	tri2->filled = true;

	//Add triangles to the world
	world->addGeometry(tri1);
	world->addGeometry(tri2);

	return success;
}

void close() {
	//Clear our classes
	delete text;
	text = nullptr;
	delete world;
	world = nullptr;
	delete screen;
	screen = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	//TTF_Quit();
	SDL_Quit();

	//Close the Font Manager
	FontManager::s()->close();

	//Close the log
	Log::s()->close();
}

void update() {
	world->update();
	sprite->angle += 0.2;
}

void render() {
	//Clear screen
	screen->clearScreen();

	//Render world stuff
	world->render();

	//Render the text
	text->render();
}

int main(int argc, char* args[]) {
	Log::s()->logInfo("Starting...");

	//Initialize main components.
	Log::s()->logInfo("Screen is being created");
	screen = new Screen("Game v0.003", 800, 600);
	Log::s()->logInfo("Screen was created");

	//Start up SDL and create window.
	Log::s()->logInfo("Initializing...");
	if(!init())	{
		printf("Failed to initialize!\n");
	} else {
		Log::s()->logInfo("Initialization was successfull");

		//Load media
		Log::s()->logInfo("Loading media...");
		if(!loadMedia()) {
			printf("Failed to load media!\n");
		} else {
			Log::s()->logInfo("Loading media was successfull");

			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while(!quit) {
				//Handle events on queue
				while(SDL_PollEvent(&e) != 0) {
					//User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}

					//User presses a key
					else if (e.type == SDL_KEYDOWN) {
						//Select surfaces based on key press
						switch (e.key.keysym.sym) {
						case SDLK_UP:
							sprite->animations->play("cycle");
							break;

						case SDLK_DOWN:
							sprite->animations->stop();
							break;

						case SDLK_LEFT:
							sprite->animations->pause();
							break;

						case SDLK_RIGHT:
							sprite->animations->resume();
							break;

						case SDLK_a:
							sprite->setAnchor(0, 0);
							break;

						case SDLK_s:
							sprite->setAnchor(0.5, 0.5);
							break;

						case SDLK_d:
							sprite->setAnchor(1, 1);
							break;

						case SDLK_f:
							sprite->setAnchor(0.5, 1);
							break;

						case SDLK_g:
							sprite->setAnchor(2, -1);
							break;

						default:
							break;
						}
					}
				}

				//First update
				update();

				//Then render
				render();

				////Render filled square to screen
				//SDL_Rect fillRect = { screen->widthFourth, screen->heightFourth, screen->widthHalf, screen->heightHalf };
				//screen->renderFilledSquare(&fillRect, Colors::Red);

				////Change viewport to be the right bottom of the screen
				//SDL_Rect viewportRightBottom = { screen->widthHalf, screen->heightHalf, screen->widthHalf, screen->heightHalf };
				//screen->setViewport(&viewportRightBottom);

				//	//Render border-only square to screen
				//	SDL_Rect drawRect = { screen->viewportWidth / 4, screen->viewportHeight / 4, screen->viewportWidth / 2, screen->viewportHeight / 2 };
				//	screen->renderDrawnSquare(&drawRect, Colors::Blue);

				////Restore the viewport to the normal position
				//screen->restoreNormalViewport();

				////Render point to screen
				//SDL_Point greenPoint = { screen->widthHalf, screen->heightHalf };
				//screen->renderPoint(&greenPoint, Colors::Green);

				//Update screen
				screen->updateScreen();
			}
		}
	}

	//TODO Add better logs, to divide into font loading, sprite loading, etc.

	//Free resources and close SDL
	Log::s()->logInfo("Closing...");
	close();
	
	//Checks for Memory Leaks
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	if (_CrtDumpMemoryLeaks() == 0) {
		std::cout << std::endl << "NO Memory Leaks! Be Proud!!!" << std::endl;
	}

	getchar();

	return 0;
}