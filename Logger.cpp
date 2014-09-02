#include "Logger.h"

namespace Logger
{
	// define log level strings here
	const string LogLevelStrings[] = { "debug", "info", "WARNING", "ERROR" };

	bool Logger::initialized = false;
	ofstream* Logger::logstream = NULL;
	LogLevel Logger::minLogLevel = LINFO;

	Logger::Logger()
	{
		this->freeLogging = true;
	}

	Logger::~Logger()
	{
		// only write to log/output if logging level is at least at minimum logging level
		if (this->logLevel >= Logger::minLogLevel)
		{
			if (!freeLogging)
				os << endl;

			// write to log file
			if (Logger::initialized)
			{
				(*this->logstream) << os.str();
				(*this->logstream).flush();
			}
			
			// also write to output
			if (outputMode == STD_ERR)
			{
				cerr << os.str();
				cerr.flush();
			}
			else if (outputMode == STD_OUT)
			{
				cout << os.str();
				cout.flush();
			}
		}
	}

	void Logger::initialize(string logPath)
	{
		// You can change the default minimum logging level here
		Logger::minLogLevel = LINFO;

		// create new file log stream object
		Logger::logstream = new ofstream(logPath.c_str(), std::ios_base::app);

		// You can customize the initial logging output below
		(*Logger::logstream) << "========== START: " << DateTimeHelper::getDateTime() << " ==========" << endl << endl;

		// initialized and ready to write to log file
		Logger::initialized = true;
	}

	void Logger::setLogLevel(LogLevel level)
	{
		Logger::minLogLevel = level;
	}

	void Logger::finalize()
	{
		Logger::initialized = false;
		if (Logger::logstream != NULL)
		{
			// You can customize the final logging output below
			(*Logger::logstream) << endl << "========== END: " << DateTimeHelper::getDateTime() << " ==========" << endl << endl;

			// close file log stream
			Logger::logstream->close();

			// delete it
			delete Logger::logstream;
		}
	}

	ostringstream& Logger::log()
	{
		// You can change the default logging behavior here
		this->logLevel = LINFO;
		this->outputMode = STD_OUT;

		return os;
	}

	ostringstream& Logger::log(LogLevel level)
	{
		// You can change here whether to print to stdout or stderr 
		// depending on the logging level passed
		if (level >= LWARNING)
			return log(level, STD_ERR);
		else
			return log(level, STD_OUT);
	}

	ostringstream& Logger::log(LogLevel level, OutputMode mode)
	{
		this->freeLogging = false;

		if (!Logger::initialized)
			return log();

		this->logLevel = level;
		this->outputMode = mode;

		// You can customize below to control logging output formatting
		// The default is "[time_elapsed] (log_level) message"
		os << "[" << DateTimeHelper::getTimeElapsed() << "] "
			<< "(" << LogLevelStrings[level] << ") ";
		
		return os;
	}

	double DateTimeHelper::getTimeElapsed()
	{
		return (double)clock()/CLOCKS_PER_SEC;
	}

	string DateTimeHelper::getDateTime()
	{
		time_t t = time(0);   // get time now
		struct tm * now = localtime( & t );
		stringstream ss;
		ss << (now->tm_year + 1900) << '-' 
			 << (now->tm_mon + 1) << '-'
			 <<  now->tm_mday << " "
			 << now->tm_hour << ":"
			 << now->tm_min << ":"
			 << now->tm_sec;
		return ss.str();
	}
}