#ifndef ANIMATION_H
#define ANIMATION_H

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

class Animation {
	/*************** Variables ***************/
private:
	//The frames that this animation consist of
	std::vector<Uint16>					frames;

	//Animation goes to this frame, if it goes above, currentFrame is set to 0
	Uint16								maxIndex;

	//Increments the index, it allows for different types of frame increment
	Sint16								indexInc;

	//The current rendering frame of the animation
	Uint16								currentFrame;

	//The current index points to the current Frame in the frame array
	Uint16								currentIndex;

	//The velocity at which the frames change
	Uint16								frameRate;

	//The time at which the frames change, equal to frameRate/second
	float								timeRate;

	//The last time at which the frame changed
	long								oldTime;
	
	//Best explained with an example: 5 frames, it increments and decrements like so: 0-1-2-3-4-3-2-1-0-1-2-... and so on and so forth
	bool								yoyo;

	//Is the animation paused? If paused and stopped is false, then it's playing; if paused is true, stopped can not be true
	bool								paused;
	
	//Is the animation stopped? If stopped and paused is false, then it's playing; if stopped is true, paused can not be true
	bool								stopped;

protected:

public:
	//Name of this animation, used to uniquely identify an animation
	std::string							name;

	/*************** Contructors & Destructors ***************/
public:
	Animation();
	Animation(std::string name, std::vector<Uint16> frames, Uint16 frameRate = 500, Sint16 indexInc = 1, bool yoyo = false);
	~Animation();

	/*************** Methods ***************/
private:

protected:

public:
	//Updates this animation
	void						update();

	//Resets the animation
	void						reset();

	//Gets the current frame of this animation
	Uint16						getCurrentFrame() const;

	//Gets the current index of this animation
	Uint16						getCurrentIndex() const;

	//Sets the frame rate to the given value
	void						setFrameRate(const Uint16 frameRate);

	//Gets the frame rate of this animation
	Uint16						getFrameRate() const;

	//Sets the index increment to the given value
	void						setIndexInc(const Uint16 indexInc);

	//Gets the index increment of this animation
	Uint16						getIndexInc() const;

	//Sets yoyo to the given value
	void						setYoyo(const bool yoyo);

	//is this animation set to use yoyo
	bool						isYoyo() const;

	//Pause the current animation
	void						pause();

	//Is the current animation paused?
	bool						isPaused() const;

	//Plays the current animation
	void						play();

	//Is the current animation playing?
	bool						isPlaying() const;

	//Stops the current animation
	void						stop();

	//Is the current animation stopped?
	bool						isStopped() const;

	//Resumes the current animation
	void						resume();	
};

#endif