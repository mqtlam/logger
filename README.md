logger
======

Another portable, lightweight and hackable logging utility for C++.

## Usage

Usage is extremely easy:

1. Add `Logger.h` and `Logger.cpp` files to your project.
2. Include the `Logger.h` in your project with `#include "Logger.h"`.
3. Initialize the Logger by running `LOG_INITIALIZE("logfilenamehere.txt")`.
4. Write to the log by using `LOG() << "Your message here"`.
5. Somewhere near the end of your program, run `LOG_FINALIZE()`.

See `demo.cpp` for a demo with more usage examples:

```
// must call this before using Logger
// if not called before using LOG(), then 
// LOG() simply outputs to stdout/stderr
LOG_INITIALIZE("log.txt");

// write freely to log
LOG() << "Hello World! ";
LOG() << "Write to log freely...." << std::endl << std::endl;

// write debug message to log
// note that it automatically adds endl to the end
LOG(LDEBUG) << "Debug message. " 
	"This should not be printed since default minimum logging level is at INFO.";

// set minimum logging level to DEBUG
// any message with logging level >= DEBUG will be printed now
LOG_SET_LEVEL(LDEBUG);

// write to debug message to log
LOG(LDEBUG) << "Debug message. "
	"This should be printed since default minimum logging level is now at DEBUG.";

// write normal message to log
LOG(LINFO) << "Normal message.";

// write warning message to log
LOG(LWARNING) << "Warning message.";

// write error message to log
LOG(LERROR) << "Error message.";

// must call this before exiting program
// to release the log file handler
LOG_FINALIZE();

```

## Extensions

This logging utility is also very hackable, i.e. you can customize it to your liking. Read the comments in the Logger class.

## Documentation

Optionally use doxygen to generate the documentation for the Logger class.