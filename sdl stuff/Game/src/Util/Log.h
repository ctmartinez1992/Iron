#ifndef LOG_H
#define LOG_H

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

//SDL

//C++
#include <fstream>
#include <iostream>
#include <cstdarg>
#include <string>
#include <ctime>

//OWN

#define LOGGER Log::getLogger()

class Log {	
	/*************** Variables ***************/
private:
	//Pointer to the unique logger
	static Log*						_s;

	//Name of the file
	static const std::string		fileName;

	//The stream object, writes to the file
	static std::ofstream			logFile;

protected:

public:

	/*************** Contructors & Destructors ***************/
public:
	Log();
	~Log();

	/*************** Methods ***************/
private:
	
protected:

public:
	//Singleton get
	static Log*						s();

	//Variable length log function
	void							log(const char * format, ...);

	//Logs a message
	void							log(const std::string& message);

	//Overload write operator
	Log&							operator<<(const std::string& message);


private:
	//Overload assign operator
	Log&							operator=(const Log&) { return *this; };
};
#endif