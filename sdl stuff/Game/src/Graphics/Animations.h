#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

//SDL
#include <SDL.h>
#include <SDL_image.h>

//C++
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

//OWN
#include "Animation.h"

class Animations {
	/*************** Variables ***************/
private:
	//All animations stored by this class, will be associated to classes like Sprite
	std::vector<Animation*>			animations;

	//Number of animations stored in the vector
	Uint16							nAnimations;

protected:

public:
	//The animation that is currently playing
	Animation*						currentAnimation;

	//The state of the current animation
	std::string						state;

	/*************** Contructors & Destructors ***************/
public:
	Animations();
	~Animations();

	/*************** Methods ***************/
private:

protected:

public:
	//Updates this animation
	void						update();

	//Adds an animation to the vector
	void						addAnimation(std::string name, std::vector<Uint16> frames, Uint16 frameRate = 500, Sint16 indexInc = 1, bool yoyo = false);

	//Plays the animation with the passed name
	void						play(std::string name);

	//Stops the animation that is currently playing
	void						stop();

	//Pauses the animation that is currently playing
	void						pause();

	//Resumes the the current animation, animation should be paused
	void						resume();
};

#endif