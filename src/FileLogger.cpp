/**
 * ConsoleLogger.hpp
 *
 * log++ - Intuitive logging library for C++ written by Simon Cahill.
 */

 /****************************
  *	    Local Includes	    *
  ****************************/
#include "FileLogger.hpp"

  /***************************
   *	    System Includes    *
   ***************************/
#include <iostream>
#include <ostream>

namespace logpp {

    using std::iostream;
    using std::ostream;


    /**
    * @brief Construct a new fileLogger::fileLogger object
    *
    * @param logName The name for this logger.
    * @param maxLogLevel The maximum logging level to log.
    * @param filename The path/to/file for printing in console
    * @param bufferSize The maximum buffer size before flushing.
    * @param flushBufferAfterWrite Indicates whether to flush the buffer after each write to it.
    */
    FileLogger::FileLogger (string logName, LogLevel maxLogLevel, string filename, uint32_t bufferSize, bool flushBufferAfterWrite) :
        ILogger(logName, maxLogLevel, bufferSize, flushBufferAfterWrite), 
        _filename(filename){}

    /**
     * @brief Destroy the fileLogger::fileLogger object
     */
    FileLogger::~FileLogger () {}
}