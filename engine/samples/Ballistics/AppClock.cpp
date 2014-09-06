#include "AppClock.h"

AppClock*				AppClock::_s = nullptr;

static bool				qpcFlag;			/*!< Hold internal timing data for the performance counter. */

AppClock::AppClock()
{
}

AppClock::AppClock(const AppClock&)
{
}

AppClock::~AppClock()
{
}

#if (__APPLE__ || __unix)
	#define TIMING_UNIX	1

	#include <stdlib.h>
	#include <sys/time.h>
#else
	#define TIMING_WINDOWS 1

	#include <windows.h>
	#include <mmsystem.h>

	static double		qpcFrequency;
#endif

/**
* Returns the processor timestamp.
* The processor time stamp records the number of clock cycles since the last reset.
*/
#if TIMING_WINDOWS
	unsigned long systemClock() {
		//Invokes the inline assembler.
		__asm {
			rdtsc;
		}
	}
#endif

unsigned long AppClock::systemTime() {
#if TIMING_UNIX
	struct timeval tv;
	gettimeofday(&tv, 0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
#else
    if(qpcFlag) {
        static unsigned long long qpcMillisPerTick;
        QueryPerformanceCounter((LARGE_INTEGER*)&qpcMillisPerTick);
        return (unsigned)(qpcMillisPerTick * qpcFrequency);
    } else {
        return unsigned(timeGetTime());
    }
#endif
}

void AppClock::start() {
#if TIMING_UNIX
    qpcFlag = false;
#else
    unsigned long long time;
    qpcFlag = QueryPerformanceFrequency((LARGE_INTEGER*)&time) > 0;
	if (qpcFlag) {
		qpcFrequency = 1000.0 / time;
	}
#endif
}

// Retrieves the global frame info instance
AppClock* AppClock::s() {
	if (_s == nullptr) {
		_s = new AppClock();
	}

	return _s;
}

void AppClock::update() {
	s();
	if (!_s) {
		return;
	}

    if (!_s->paused) {
        _s->fN++;
    }

    //Time data
    unsigned long sysTime = systemTime();
	_s->lastFSpan = sysTime - _s->lastFTS;
	_s->lastFTS = sysTime;

    //Tick data
    unsigned long sysClock = getClock();
    _s->lastFCT = sysClock - _s->lastFCS;
    _s->lastFCS = sysClock;

	//FPS
    if (_s->fN > 1) {
        if (_s->avgFSpan <= 0) {
            _s->avgFSpan = (double)_s->lastFSpan;
        } else {
			_s->avgFSpan *= 0.99;
			_s->avgFSpan += 0.01 * (double)_s->lastFSpan;
            _s->fps = (float)(1000.0 / _s->avgFSpan);
        }
    }
}

void AppClock::init() {
    start();
	s();

	_s->fN = 0;
	_s->lastFSpan = 0;
    _s->lastFTS = systemTime();
    _s->lastFCS = getClock();
	_s->lastFCT = 0;
	_s->fps = 0;
	_s->avgFSpan = 0;
    _s->paused = false;
}

void AppClock::destroy() {
	delete _s;
	_s = NULL;
}

unsigned long AppClock::getTime() {
	return systemTime();
}

unsigned long AppClock::getClock() {
#if TIMING_UNIX
	struct timeval tv;
	gettimeofday(&tv, 0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
#else
	return systemClock();
#endif
}
