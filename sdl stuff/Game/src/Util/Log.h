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

//Use [INFO], [WARNING], [ERROR], [DEBUG] accordingly, no point in wasting time implementing it

class Log {	
	/*************** Variables ***************/
private:
	//Pointer to the unique logger
	static Log*						_s;

	//Name of the file
	static const std::string		fileName;

	//The stream object, writes to the file
	static std::ofstream			logFile;

	//Booleans to control the log types
	static bool						showDebug;
	static bool						showInfo;
	static bool						showError;
	static bool						showWarning;

protected:

public:

	/*************** Contructors & Destructors ***************/
public:
	Log();
	virtual ~Log();

	/*************** Methods ***************/
private:
	//Don't implement
	Log&							operator=(const Log&) { return *this; }; 

	//Don't implement
	Log(Log const&);

	//Overused function
	void							log(const std::string type, const std::string& message);
	
protected:

public:
	//Singleton get
	static Log*						s();

	//Logs a debug message
	void							logDebug(const std::string& message);
	//Logs an info message
	void							logInfo(const std::string& message);
	//Logs an error message
	void							logError(const std::string& message);
	//Logs a warning message
	void							logWarning(const std::string& message);

	//Overload write operator
	Log&							operator<<(const std::string& message);

	//Closes the log
	void							close();
};
#endif