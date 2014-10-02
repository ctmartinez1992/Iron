#include "Errors.h"

#include <cstdlib>
#include <sdl/SDL.h>
#include <iostream>

namespace iron {

	namespace graphics {

		//Prints out an error message and exits the game.
		void fatalError(std::string errorString) {
			std::cout << errorString << std::endl;
			std::cout << "Enter any key to quit...";
			int tmp;
			std::cin >> tmp;
			SDL_Quit();
			exit(100);
		}
    }
}