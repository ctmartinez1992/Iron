#define _CRTDBG_MAP_ALLOC
#include "Animations.h"

Animations::Animations() : animations(), nAnimations(0), currentAnimation(nullptr), state("There is no animation!")
{
}

Animations::~Animations() {
	for (size_t i = 0; i < animations.size(); ++i) {
		delete animations[i];
		animations[i] = nullptr;
	}

	currentAnimation = nullptr;
}

void Animations::update() {
	if (nAnimations > 0) {
		for (std::vector<Animation*>::iterator it = animations.begin(); it != animations.end(); ++it) {
			(*it)->update();
		}
	}
}

void Animations::addAnimation(std::string name, std::vector<Uint16> frames, Uint16 frameRate, Sint16 indexInc, bool yoyo) {
	//Push the animation into the vector and increment the counter
	this->animations.push_back(new Animation(name, frames, frameRate, indexInc, yoyo));
	nAnimations++;
	state = "Animation[" + name + "] is loaded but has no state...";
	Log::s()->logDebug("Animation (" + name + ") was added");
}

void Animations::play(std::string name) {
	//Is there animation?
	if (nAnimations == 0) {
		return;
	}

	//Stop the current animation, if there's any
	if (currentAnimation != nullptr) {
		currentAnimation->stop();
	}

	//Find the animation by searching for the name
	for (size_t i = 0; i < animations.size(); ++i) {
		if (animations[i]->name.compare(name) == 0) {
			animations[i]->play();
			currentAnimation = animations[i];
			state = "Animation[" + name + "] is playing!";
		}
	}
}

void Animations::stop() {
	//Is there animation?
	if (nAnimations == 0) {
		return;
	}

	if (currentAnimation != nullptr) {
		currentAnimation->stop();
		state = "Animation[" + currentAnimation->name + "] is stopped!";
	}
}

void Animations::pause() {
	if (nAnimations == 0) {
		return;
	}

	if (currentAnimation != nullptr) {
		currentAnimation->pause();
		state = "Animation[" + currentAnimation->name + "] is paused!";
	}
}

void Animations::resume() {
	if (nAnimations == 0) {
		return;
	}

	if (currentAnimation != nullptr) {
		currentAnimation->resume();
		state = "Animation[" + currentAnimation->name + "] is playing!";
	}
}