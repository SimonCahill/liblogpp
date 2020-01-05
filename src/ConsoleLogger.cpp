/**
 * ConsoleLogger.hpp
 *
 * log++ - Intuitive logging library for C++ written by Simon Cahill.
 */

/****************************
 *	    Local Includes	    *
 ****************************/
 #include "ConsoleLogger.hpp"

/***************************
 *	    System Includes    *
 ***************************/
#include <iostream>
#include <ostream>

namespace logpp {

    using std::iostream;
    using std::ostream;

    /**
     * @brief Construct a new Console Logger:: Console Logger object
     * 
     * @param logName The name for this logger.
     * @param maxLogLevel The maximum logging level to log.
     * @param outputBadLogsToStderr Indicates whether to output bad logs to std error or not.
     * @param bufferSize The maximum buffer size before flushing.
     * @param flushBufferAfterWrite Indicates whether to flush the buffer after each write to it.
     */
    ConsoleLogger::ConsoleLogger(string logName, LogLevel maxLogLevel, bool outputBadLogsToStderr, uint32_t bufferSize, bool flushBufferAfterWrite):
    ILogger(logName, maxLogLevel, flushBufferAfterWrite, bufferSize) {
        setOutputBadLogsToStderr(outputBadLogsToStderr);
    }

    /**
     * @brief Destroy the Console Logger:: Console Logger object
     */
    ConsoleLogger::~ConsoleLogger() {}

    /**
     * @brief Flushes the underlying buffer to its respective output.
     */
    void ConsoleLogger::flushBuffer() {
        using std::cout;
        using std::endl;

        // TODO: Implement functionality where bad logs are output to cerr if desired.
        // This will require overriding logMessage()
        cout << getLogBuffer().str() << endl;
        getLogBuffer().clear();
    }

    /**
     * @brief Overridden method; logs messages to the internal buffer or standard error output.
     * 
     * @remarks This method is overridden. While the core functionality remains the same, 
     * the major difference is that "bad" logs are automatically redirected to stderr, instead of 
     * being buffered.
     * A "bad" log is any log level >= 4.
     * 
     * @param level The log level of the message.
     * @param msg The message to be output.
     */
    void ConsoleLogger::logMessage(LogLevel level, string msg) {
        using std::cerr;
        using std::endl;

        if (outputBadLogsToStderr() && isBadLog(level)) {
            // Bypass log buffer and print directly to stderr.
            cerr << msg << endl;
            return;
        }

        ILogger::logMessage(level, msg);
    }

}
