#ifndef IRON_DEMO_APPCLOCK_H_
#define IRON_DEMO_APPCLOCK_H_

/*! \brief Class that holds data related to frames and game time.
*
* This class stores data about time between frames, frame numbers, frames per second,
* if the game is paused, and a few supporting functions.
*/
class AppClock {
	/****************************** Variables ******************************/
private:

protected:

public:
	static AppClock*		_s;					/*!< Pointer to the unique AppClock (Singleton). */
	
	unsigned long			fN;					/*!< The current frame number. */

	unsigned long			lastFSpan;			/*!< Last frame's span in milliseconds. */

	unsigned long			lastFTS;			/*!< Last frame's timestamp in milliseconds. */

	unsigned long			lastFCS;			/*!< Last frame's clockstamp. */

	unsigned long			lastFCT;			/*!< Last frame's clock ticks. */

	float					fps;				/*!< Current frames per second. */

	double					avgFSpan;		/*!< Average duration of all frames from start. */

	bool					paused;				/*!< Is the application paused? */

	/****************************** Contructors & Destructors ******************************/
public:
	/**
	* Virtual Destructor.
	*/
	virtual ~AppClock();

private:
	AppClock();

	AppClock(const AppClock&);
	
	/****************************** Methods ******************************/
private:
	/**
	* Returns the system time.
	*
	* @return The system time.
	*/
	static unsigned long systemTime();

	/**
	* Sets up the timing system and registers the performance timer.
	*/
	static void start();

protected:

public:
	/**
	* Returns the singleton object.
	*
	* @return The unique singleton object.
	*/
	static AppClock* s();

	/**
	* Initialises the variables with the appropriate values.
	*/
	static void init();

	/**
	* Cleans the singleton.
	*/
	static void destroy();

	/**
	* Should be call every single frame to update the variables and maintain a properly updated system.
	*/
	static void update();

	/**
	* Returns the system time in milliseconds.
	*
	* @return The system time in milliseconds.
	*/
	static unsigned long getTime();

	/**
	* Returns the clock ticks since the beginning.
	*
	* @return The clock ticks since the beginning.
	*/
	static unsigned long getClock();

	/****************************** Operators Overloading ******************************/
private:
	AppClock& operator=(const AppClock&);

protected:

public:

};

#endif