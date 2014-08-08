#include "Log.h"

namespace iron {

	const std::string	Log::fileName = "log.txt";
	Log*				Log::_s = nullptr;
	std::ofstream		Log::logFile;
	bool				Log::showDebug = true;
	bool				Log::showInfo = true;
	bool				Log::showError = true;
	bool				Log::showWarning = true;

	Log::Log()
	{
	}

	Log::~Log()
	{
	}

	void Log::log(const std::string& type, const std::string& message, const long& line, const std::string& function, const std::string& file) {
		//Get the current time
		time_t t = time(0);
		tm *cT = new tm();
		gmtime_s(cT, &t);

		//Find the name of the file
		unsigned found = file.find_last_of("/\\");

		logFile << "[" << cT->tm_hour << ":" << cT->tm_min << ":" << cT->tm_sec << "]:"
			<< "[" << line << "]:"
			<< "[" << function << "]:"
			<< "[" << file.substr(found + 1) << "]:"
			<< type << " - "
			<< message << "\n";

		delete cT;
	}
	
	Log* Log::s(){
		if (_s == nullptr) {
			_s = new Log();
			logFile.open(fileName.c_str(), std::ofstream::out | std::ofstream::trunc);
		}

		return _s;
	}

	void Log::logDebug(const std::string& message, const long& line, const std::string& function, const std::string& file) {
		if (!showDebug) {
			return;
		}

		log("[DEBUG]", message, line, function, file);
	}

	void Log::logInfo(const std::string& message, const long& line, const std::string& function, const std::string& file) {
		if (!showInfo) {
			return;
		}

		log("[INFO]", message, line, function, file);
	}

	void Log::logError(const std::string& message, const long& line, const std::string& function, const std::string& file) {
		if (!showError) {
			return;
		}

		log("[ERROR]", message, line, function, file);
	}

	void Log::logWarning(const std::string& message, const long& line, const std::string& function, const std::string& file) {
		if (!showWarning) {
			return;
		}

		log("[WARNING]", message, line, function, file);
	}

	Log& Log::operator<<(const std::string& message) {
		time_t t = time(0);
		tm *cT = new tm();
		gmtime_s(cT, &t);

		logFile << "[" << cT->tm_hour << ":" << cT->tm_min << ":" << cT->tm_sec << "]: ";
		logFile << message << "\n";

		delete cT;
		return *this;
	}

	void Log::close() {
		logFile.close();
		delete _s;
		_s = nullptr;
	}
}