#include "Log.h"

const std::string	Log::fileName = "Log.txt";
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

void Log::log(const std::string type, const std::string& message) {
	time_t t = time(0);
	tm *cT = new tm();
	gmtime_s(cT, &t);

	logFile << "[" << cT->tm_hour << ":" << cT->tm_min << ":" << cT->tm_sec << "]: " << type << " - ";
	logFile << message << "\n";

	delete cT;
}

Log* Log::s(){
	if (_s == nullptr){
		_s = new Log();
		logFile.open(fileName.c_str(), std::ofstream::out | std::ofstream::trunc);
	}

	return _s;
}

void Log::logDebug(const std::string& message) {
	if (!showDebug) {
		return;
	}

	log("[DEBUG]", message);
}

void Log::logInfo(const std::string& message) {
	if (!showInfo) {
		return;
	}

	log("[INFO]", message);
}

void Log::logError(const std::string& message) {
	if (!showError) {
		return;
	}

	log("[ERROR]", message);
}

void Log::logWarning(const std::string& message) {
	if (!showWarning) {
		return;
	}

	log("[WARNING]", message);
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