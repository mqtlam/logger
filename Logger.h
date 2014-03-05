#ifndef Logger_H
#define Logger_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>

// BEGIN MACROS

// Usage examples: LOG() << "raw message to log and stdout"
//	or LOG(WARNING) << "auto formatted warning message to log and stderr"
//	or LOG(ERROR, FILE_ONLY) << "auto formatted error message only to log file"
#define LOG Logger::Logger().log

#define LOG_INITIALIZE Logger::Logger::initialize
#define LOG_SET_LEVEL Logger::Logger::setLogLevel
#define LOG_FINALIZE Logger::Logger::finalize

// END MACROS

namespace Logger
{
	using namespace std;

	/*!
	 * Enumeration of all logging levels.
	 * Ordered from lowest to largest logging level.
	 */
	enum LogLevel { DEBUG=0, INFO, WARNING, ERROR };
	
	/*!
	 * Corresponding strings to logging levels enum.
	 * Defined in Logger.cpp
	 */
	const extern string LogLevelStrings[];

	/*!
	 * Enumeration of all output modes.
	 * FILE_ONLY: write to log file only
	 * STD_ERR: write to log file and print to stderr
	 * STD_OUT: write to log file and print to stdout
	 */
	enum OutputMode { FILE_ONLY, STD_ERR, STD_OUT };

	/*!
	 * Basic logger class for logging errors and debugging.
	 */
	class Logger
	{
		// Globally set settings
	protected:
		static bool initialized; //!< true if Logger initialized
		static ofstream* logstream; //!< log file stream object
		static LogLevel minLogLevel; //!< current minimum logging level
		// You can add more static members here and pass values from initialize()
		// to initiatilize these members. Useful for storing other data for logging, like process ID.

		// For logging
	protected:
		LogLevel logLevel; //!< log level of LOG()  call
		OutputMode outputMode; //!< output mode of LOG() call
		ostringstream os; //!< string stream object
		bool freeLogging; //!< true implies do not automatically add endl to end of string stream

	public:
		/*!
		 * Construct a Logger object.
		 */
		Logger();
		
		/*!
		 * Destruct a Logger object.
		 */
		~Logger();

		/*!
		 * Initialize the logger. Must be called before making log calls.
		 * 
		 * You can extend this call by adding more arguments and setting new static members.
		 * @param[in] logPath Path to the log file to open
		 */
		static void initialize(string logPath);

		/*!
		 * Set the logging level.
		 * 
		 * Default is INFO. Set to DEBUG to see all messages.
		 * @param[in] level Minimum logging level to display messages: DEBUG|INFO|WARNING|ERROR
		 */
		static void setLogLevel(LogLevel level);

		/*!
		 * Finalize the logger. Must be called before exiting application to release file handler.
		 */
		static void finalize();

		/*!
		 * Write to the log raw stream.
		 * @return String stream object for internal use
		 */
		ostringstream& log();

		/*!
		 * Write to the log using the specified logging level.
		 * @param[in] level Logging level of message: DEBUG|INFO|WARNING|ERROR
		 * @return String stream object for internal use
		 */
		ostringstream& log(LogLevel level);

		/*!
		 * Write to the log using the specified logging level 
		 * and writing mode.
		 * @param[in] level Logging level of message: DEBUG|INFO|WARNING|ERROR
		 * @param[in] mode Output mode: FILE_ONLY|STD_ERR|STD_OUT
		 * @return String stream object for internal use
		 */
		ostringstream& log(LogLevel level, OutputMode mode);
	};

	/*!
	 * Basic date and time helper class.
	 */
	class DateTimeHelper
	{
	public:
		/*!
		 * Get the time elapsed since program started (in milliseconds).
		 * @return Milliseconds elapsed since program started
		 */
		static double getTimeElapsed();

		/*!
		 * Get the current date and time as a string.
		 * @return Current date and time string
		 */
		static string getDateTime();
	};
}

#endif