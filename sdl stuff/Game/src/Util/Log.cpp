#include "Log.h"

const std::string	Log::fileName = "Log.txt";
Log*				Log::_s = nullptr;
std::ofstream		Log::logFile;

Log::Log()
{
}

Log::~Log()
{
}

Log* Log::s(){
	if (_s == nullptr){
		_s = new Log();
		logFile.open(fileName.c_str(), std::ofstream::out | std::ofstream::app);
	}

	return _s;
}

void Log::log(const char * format, ...) {
	char message[256];

	va_list args;
	va_start(args, format);
		vsprintf(message, format, args);
		time_t t = time(0);
		tm *cT = gmtime(&t);
		logFile << "\n[" << cT->tm_hour << ":" << cT->tm_min << ":" << cT->tm_sec << "]:\t";
		logFile << message;
	va_end(args);
}

void Log::log(const std::string& message) {
	time_t t = time(0);
	tm *cT = gmtime(&t);
	logFile << "\n[" << cT->tm_hour << ":" << cT->tm_min << ":" << cT->tm_sec << "]:\t";
	logFile << message;
}

Log& Log::operator<<(const std::string& message) {
	time_t t = time(0);
	tm *cT = gmtime(&t);
	logFile << "\n[" << cT->tm_hour << ":" << cT->tm_min << ":" << cT->tm_sec << "]:\t";
	logFile << message;
	return *this;
}