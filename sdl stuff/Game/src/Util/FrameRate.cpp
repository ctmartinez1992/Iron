#include "FrameRate.h"

FrameRate::FrameRate() : rate(FPS_DEFAULT), baseTicks(getTicks()), lastTicks(baseTicks), frameCount(0), rateTicks((1000.0f / (float)FPS_DEFAULT))
{
}

FrameRate::~FrameRate()
{
}

Uint32 FrameRate::getTicks() {
	Uint32 ticks = SDL_GetTicks();
	return (ticks == 0) ? 1 : ticks;
}

void FrameRate::setFrameRate(Uint32 rate) {
	if (rate >= FPS_LOWEST && rate <= FPS_HIGHEST) {
		frameCount = 0;
		rate = rate;
		rateTicks = (1000.0f / (float)rate);
	} else {
		Log::s()->logInfo("setFrameRate received a value that not acceptable, it must be between [" + FPS_LOWEST + "] and [" + FPS_HIGHEST + "], but it received [" + rate + "]");
	}
}

int FrameRate::getFrameRate() {
	return (int) rate;
}

int FrameRate::getFrameCount() {
	return frameCount;
}

Uint32 FrameRate::frameRateDelay() {
	Uint32 currentTicks = 0;
	Uint32 targetTicks = 0;
	Uint32 delay = 0;
	Uint32 passedTime = 0;

	//Go to next frame
	frameCount++;

	//Calculate the ticks
	currentTicks = getTicks();
	passedTime = currentTicks - lastTicks;
	lastTicks = currentTicks;
	targetTicks = baseTicks + (Uint32) ((float) frameCount * rateTicks);

	//Introduce the delay
	if (currentTicks <= targetTicks) {
		delay = targetTicks - currentTicks;
		SDL_Delay(delay);
	} else {
		frameCount = 0;
		baseTicks = getTicks();
	}

	return passedTime;
}
