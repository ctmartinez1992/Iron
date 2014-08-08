#define _CRTDBG_MAP_ALLOC
#include "Animation.h"

Animation::Animation() : name(""), maxIndex(0), indexInc(1), currentFrame(0), currentIndex(0),
						 frameRate(100), oldTime(0), yoyo(false), paused(false), stopped(true)
{
	frames = { 0 };
	currentFrame = frames[currentIndex];
	maxIndex = frames.size() - 1;
	timeRate = (float) (1000.0 / frameRate);
}

Animation::Animation(std::string name, std::vector<Uint16> frames, Uint16 frameRate, Sint16 indexInc, bool yoyo) : 
	name(name), maxIndex(0), indexInc(indexInc), currentFrame(0), currentIndex(0),
	frameRate(frameRate), oldTime(0), yoyo(yoyo), paused(false), stopped(true)
{
	this->frames = frames;
	currentFrame = frames[currentIndex];
	maxIndex = frames.size() - 1;
	timeRate = (float) (1000.0 / frameRate);
}

Animation::~Animation() {
}

void Animation::update() {
	//Check if the animation is playing
	if (!isPlaying()) {
		return;
	}

	//Check if enough time as passed to pass on to the next frame
	if (((Uint32) oldTime + timeRate) > SDL_GetTicks()) {
		return;
	}

	//Update variables with current time and advance to next frame
	oldTime = SDL_GetTicks();
	currentIndex += indexInc;

	//If yoyo is true we need to handle the frame advancement in a different manner, if not then simply see if it's over the frame limit
	if (yoyo) {
		if (indexInc > 0) {
			if (currentIndex >= maxIndex) {
				indexInc *= -1;
			}
		} else {
			if (currentIndex <= 0) {
				indexInc *= -1;
			}
		}
	} else {
		if (currentIndex > maxIndex) {
			currentIndex = 0;
		}
	}

	//Clamp the values between 0 and the maxIndex
	if (currentIndex <= 0) {
		currentIndex = 0;
	}
	if (currentIndex > maxIndex) {
		currentIndex = maxIndex;
	}

	//Update the currentFrame with the new currentFrame
	currentFrame = frames[currentIndex];
}

void Animation::reset() {
	currentIndex = 0;
	currentFrame = frames[currentIndex];
	oldTime = SDL_GetTicks();
}

Uint16 Animation::getCurrentFrame() const {
	return currentFrame;
}

Uint16 Animation::getCurrentIndex() const {
	return currentIndex;
}

void Animation::setFrameRate(const Uint16 frameRate) {
	if (frameRate < 0) {
		return;
	}

	this->frameRate = frameRate;
	this->timeRate = (float) (1000.0 / frameRate);
}

Uint16 Animation::getFrameRate() const {
	return frameRate;
}

void Animation::setIndexInc(const Uint16 indexInc) {
	if (indexInc == 0) {
		return;
	}

	this->indexInc = indexInc;
}

Uint16 Animation::getIndexInc() const {
	return indexInc;
}

void Animation::setYoyo(const bool yoyo) {
	this->yoyo = yoyo;
}

bool Animation::isYoyo() const {
	return yoyo;
}

void Animation::pause() {
	this->paused = true;
	this->stopped = false;
}

bool Animation::isPaused() const {
	return (paused) && (!stopped);
}

void Animation::play() {
	this->paused = false;
	this->stopped = false;
	this->reset();
}

bool Animation::isPlaying() const {
	return (!paused) && (!stopped);
}

void Animation::stop() {
	this->paused = false;
	this->stopped = true;
	this->reset();
}

bool Animation::isStopped() const {
	return (!paused) && (stopped);
}

void Animation::resume() {
	this->paused = false;
	this->stopped = false;
}