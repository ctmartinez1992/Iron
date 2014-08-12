#ifndef LOG_H
#define LOG_H

#include "Base.h"

namespace iron {

	/*! \brief Logs messages into a file.
	*
	*  //TODO This class probably needs to be improved in a few ways but for now it works properly and it's
	*  not that much of an hassle to handle it.
	*  
	*  This class is a singleton and is used to log important messages into a file, all messages have a category
	*  ranging DEBUG, INFO, WARNING and ERROR.
	*
	*  Debug is used for debug purposes only;
	*
	*  INFO is a simple message reporting information about a certain aspect, stuff like screen resolution, system settings, etc.;
	*
	*  WARNING messages are used to report important cases that are not considered errors but should be taken into consideration;
	*
	*  ERROR messages are almost like an assert, except it doesn't crash the program;
	*
	*  Categories can be disabled and enabled to display only the ones desired by using the 4 boolean variables: showDebug;
	*  showInfo; showError; showWarning.
	*/
	class Log {
		/*************** Variables ***************/
	private:
		static Log*						_s;				/*!< Pointer to the unique logger (Singleton). */

		static const std::string		fileName;		/*!< Name of the file. */

		static std::ofstream			logFile;		/*!< The stream object, writes to the file. */

		static bool						showDebug;		/*!< Variable used to control the output of the logger. If false, this logger doesn't write DEBUG messages to the file. */
		static bool						showInfo;		/*!< Variable used to control the output of the logger. If false, this logger doesn't write INFO messages to the file. */
		static bool						showError;		/*!< Variable used to control the output of the logger. If false, this logger doesn't write ERROR messages to the file. */
		static bool						showWarning;	/*!< Variable used to control the output of the logger. If false, this logger doesn't write WARNING messages to the file. */

	protected:

	public:

		/*************** Contructors & Destructors ***************/
	public:
		/**
		* Default contructor with no operations in it.
		*/
		Log();

		/**
		* Virtual Destructor.
		*/
		virtual ~Log();

	private:
		/**
		* Don't allow the clone constructor.
		*/
		Log(Log const&);

		/*************** Methods ***************/
	private:
		/**
		* Logs the given message with the given type to the pre-determined file. It receives the line, function and file it was called from.
		*
		* @param type The type of message (DEBUG, INFO, WARNING, ERROR).
		* @param message The content of the message.
		* @param line The line this function was called from.
		* @param function The scope this function was called from.
		* @param file The The file this function was called from.
		*/
		inline void						log(const std::string& type, const std::string& message, const long& line, const std::string& function, const std::string& file);

	protected:

	public:
		//Singleton get
		static Log*						s();

		/**
		* Logs a debug message to the pre-determined file. It receives the line, function and file it was called from.
		*
		* @param message The content of the message.
		* @param line The line this function was called from.
		* @param function The scope this function was called from.
		* @param file The The file this function was called from.
		*/
		void							logDebug(const std::string& message, const long& line, const std::string& function, const std::string& file);

		/**
		* Logs an info message to the pre-determined file. It receives the line, function and file it was called from.
		*
		* @param message The content of the message.
		* @param line The line this function was called from.
		* @param function The scope this function was called from.
		* @param file The The file this function was called from.
		*/
		void							logInfo(const std::string& message, const long& line, const std::string& function, const std::string& file);
		
		/**
		* Logs an error message to the pre-determined file. It receives the line, function and file it was called from.
		*
		* @param message The content of the message.
		* @param line The line this function was called from.
		* @param function The scope this function was called from.
		* @param file The The file this function was called from.
		*/
		void							logError(const std::string& message, const long& line, const std::string& function, const std::string& file);
		
		/**
		* Logs a warning message to the pre-determined file. It receives the line, function and file it was called from.
		*
		* @param message The content of the message.
		* @param line The line this function was called from.
		* @param function The scope this function was called from.
		* @param file The The file this function was called from.
		*/
		void							logWarning(const std::string& message, const long& line, const std::string& function, const std::string& file);

		/**
		* //TODO Right now, this function behaves as a destructor which seems wrong, i'm sure there's a better way...
		* Closes the log file handler.
		*/
		void							close();

		/****************************** Operators Overloading ******************************/
	private:
		/**
		* Don't allow the equal operator.
		*/
		Log&							operator=(const Log&) { return *this; };

	protected:

	public:
		/**
		* Overload the write operator to output everything to the file.
		*/
		Log&							operator<<(const std::string& message);

	};
}
#endif