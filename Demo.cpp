#include "Logger.h"

int main(int argc, char* argv[])
{
	// must call this before using Logger
	// if not called before using LOG(), then 
	// LOG() simply outputs to stdout/stderr
	LOG_INITIALIZE("log.txt");

	// write freely to log
	LOG() << "Hello World! ";
	LOG() << "Write to log freely...." << std::endl << std::endl;

	// write debug message to log
	// note that it automatically adds endl to the end
	LOG(Logger::DEBUG) << "Debug message. " 
		"This should not be printed since default minimum logging level is at INFO.";

	// set minimum logging level to DEBUG
	// any message with logging level >= DEBUG will be printed now
	LOG_SET_LEVEL(Logger::DEBUG);

	// write to debug message to log
	LOG(Logger::DEBUG) << "Debug message. "
		"This should be printed since default minimum logging level is now at DEBUG.";

	// write normal message to log
	LOG(Logger::INFO) << "Normal message.";

	// write warning message to log
	LOG(Logger::WARNING) << "Warning message.";

	// write error message to log
	LOG(Logger::ERROR) << "Error message.";

	// must call this before exiting program
	// to release the log file handler
	LOG_FINALIZE();

	return 0;
}