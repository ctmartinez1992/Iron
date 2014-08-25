#ifndef IRON_UTIL_LOG_H
#define IRON_UTIL_LOG_H

#include "Base.h"

namespace iron {

	/*! \brief Logs messages into a file.
	*
	*  //TODO This class probably needs to be improved in a few ways but for now it works properly
	*  and it's not that much of an hassle to handle it.
	*  
	*  This class is a singleton and is used to log important messages into a file, all messages have
	*  a category ranging DEBUG, INFO, WARNING and ERROR.
	*
	*  Debug is used for debug purposes only;
	*
	*  INFO is a simple message reporting information about a certain aspect, stuff like screen
	*  resolution, system settings, etc.;
	*
	*  WARNING messages are used to report important cases that are not considered errors but should be
	*  taken into consideration;
	*
	*  ERROR messages are almost like an assert, except it doesn't crash the program;
	*
	*  Categories can be disabled and enabled to display only the ones desired by using the 4 boolean
	*  variables: showDebug; showInfo; showError; showWarning.
	*/
	class Log {
		/*************** Variables ***************/
	private:
		static Log*						_s;				/*!< Pointer to the unique logger (Singleton). */

		static const std::string		fileName;		/*!< Name of the file. */

		static std::ofstream			logFile;		/*!< The stream object, writes to the file. */

		/**
		* Used to control the output of the logger. If false, DEBUG messages aren't written.
		*/
		static bool						showDebug;

		/**
		* Used to control the output of the logger. If false, INFO messages aren't written.
		*/
		static bool						showInfo;

		/**
		* Used to control the output of the logger. If false, ERROR messages aren't written.
		*/
		static bool						showError;
		
		/**
		* Used to control the output of the logger. If false, WARNING messages aren't written.
		*/
		static bool						showWarning;

	protected:

	public:

		/*************** Contructors & Destructors ***************/
	public:
		/**
		* Virtual Destructor.
		*/
		virtual ~Log();

	private:
		Log();

		Log(const Log&);

		/*************** Methods ***************/
	private:
		/**
		* Logs the given message with the given type to the pre-determined file. It receives the line,
		* function and file it was called from.
		*
		* @param type The type of message (DEBUG, INFO, WARNING, ERROR).
		* @param message The content of the message.
		* @param line The line this function was called from.
		* @param function The scope this function was called from.
		* @param file The The file this function was called from.
		*/
		inline void	log(const std::string& type, const std::string& message, const long& line, 
			const std::string& function, const std::string& file);

	protected:

	public:
		/**
		* Returns the singleton object.
		*
		* @return The unique singleton object.
		*/
		static Log*	s();

		/**
		* Logs a debug message to the pre-determined file. It receives the line, function and file
		* it was called from.
		*
		* @param message The content of the message.
		* @param line The line this function was called from.
		* @param function The scope this function was called from.
		* @param file The The file this function was called from.
		*/
		void logDebug(const std::string& message, const long& line, const std::string& function,
			const std::string& file);

		/**
		* Logs an info message to the pre-determined file. It receives the line, function and file
		* it was called from.
		*
		* @param message The content of the message.
		* @param line The line this function was called from.
		* @param function The scope this function was called from.
		* @param file The The file this function was called from.
		*/
		void logInfo(const std::string& message, const long& line, const std::string& function,
			const std::string& file);
		
		/**
		* Logs an error message to the pre-determined file. It receives the line, function and file
		* it was called from.
		*
		* @param message The content of the message.
		* @param line The line this function was called from.
		* @param function The scope this function was called from.
		* @param file The The file this function was called from.
		*/
		void logError(const std::string& message, const long& line, const std::string& function,
			const std::string& file);
		
		/**
		* Logs a warning message to the pre-determined file. It receives the line, function and file
		* it was called from.
		*
		* @param message The content of the message.
		* @param line The line this function was called from.
		* @param function The scope this function was called from.
		* @param file The The file this function was called from.
		*/
		void logWarning(const std::string& message, const long& line, const std::string& function,
			const std::string& file);

		/**
		* //TODO Right now, this function behaves as a destructor which seems wrong, i'm sure there's
		* a better way...
		* Closes the log file handler.
		*/
		void close();

		/****************************** Operators Overloading ******************************/
	private:
		Log& operator=(const Log&);

	protected:

	public:
		/**
		* Overload the write operator to output everything to the file.
		*/
		Log& operator<<(const std::string& message);

	};
}
#endif