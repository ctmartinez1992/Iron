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
#include "Graphics/NormalTexture.h"
#include "Graphics/SpriteSheet.h"
#include "Graphics/Sprite.h"

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

//SpriteSheet test
SpriteSheet* sheet = nullptr;

//Sprite test
Sprite* sprite = nullptr;

//The screen.
Screen* screen = nullptr;

//The World, handles everything
World* world = nullptr;

bool init() {
	//Checks if the screen was initialized.
	bool successScreen = true;

	//Try to initialize the Screen class.
	if(screen == nullptr) {
		printf("The Screen class can't be initialized... It's nullptr\n");
		successScreen = false;
	} else {
		successScreen = screen->initScreen();
	}

	if(!successScreen) {
		return false;
	}

	//Create the world class
	world = new World(screen);

	//Everything went fine.
	return true;
}

bool loadMedia() {
	//Loading success flag.
	bool success = true;

	//Load a SpriteSheet
	sheet = new SpriteSheet(screen->renderer);
	if (!sheet->loadTextureAndClips("res/dots11.png", 200, 200, 4)) {
		printf("Failed to load Sprite Sheet!\n");
		success = false;
	}

	//Add the sprite sheet to the world
	world->addSpriteSheet(sheet);
	
	//Load a sprite from a sheet, clip it and throw some animations in
	sprite = new Sprite(sheet);
	SDL_Rect clip = { 0, 0, sheet->getSpriteWidth(), sheet->getSpriteHeight() };
	sprite->loadSprite(200, 200, clip, true, true, 0);
	sprite->animations->addAnimation("cycle", { 0, 1, 2, 3 }, 7, 1);
	sprite->animations->addAnimation("cycle2", { 0, 1, 2, 1, 3, 2, 1 }, 10, 1);
	sprite->animations->play("cycle");

	//Add the sprite to the world
	world->addSprite(sprite);

	return success;
}

void close() {
	//Quit SDL subsystems.
	IMG_Quit();
	SDL_Quit();

	//Clear our classes.
	delete world;
	world = nullptr;
	delete screen;
	screen = nullptr;
}

void update() {
	world->update();
	sprite->angle += 0.22;
}

void render() {
	//Clear screen
	screen->clearScreen();

	//Render world stuff
	world->render();
}

int main(int argc, char* args[]) {
	//Initialize main components.
	screen = new Screen("Game v0.002", 800, 600);

	//Start up SDL and create window.
	if(!init())	{
		printf("Failed to initialize!\n");
	} else {
		//Load media
		if(!loadMedia()) {
			printf("Failed to load media!\n");
		} else {	
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

	//Free resources and close SDL
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