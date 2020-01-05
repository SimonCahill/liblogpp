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

    using std::cerr;
    using std::cout;
    using std::endl;
    using std::iostream;
    using std::ostream;

   ConsoleLogger::ConsoleLogger(string logName, LogLevel maxLogLevel, bool outputBadLogsToStderr, uint32_t bufferSize, bool flushBufferAfterWrite):
   ILogger(logName, maxLogLevel) {
       setOutputBadLogsToStderr(outputBadLogsToStderr);
       setBufferSize(bufferSize);
       setFlushAfterWrite(flushBufferAfterWrite);
   }

   ConsoleLogger::~ConsoleLogger() {}

   void ConsoleLogger::flushBuffer() {
       // TODO: Implement functionality where bad logs are output to cerr if desired.
       // This will require overriding logMessage()
       cout << getLogBuffer().str() << endl;
   }

   void ConsoleLogger::debug(string msg, exception* except, int32_t line, string func) {
       auto level = LogLevel::Debug;
       logMessage(level, formatLogMessage(msg, level, func, line, except));
   }

   void ConsoleLogger::error(string msg, exception* except, int32_t line, string func) {
       auto level = LogLevel::Error;
       logMessage(level, formatLogMessage(msg, level, func, line, except));
   }

   void ConsoleLogger::fatal(string msg, exception* except, int32_t line, string func) {
       auto level = LogLevel::Fatal;
       logMessage(level, formatLogMessage(msg, level, func, line, except));
   }

   void ConsoleLogger::info(string msg, exception* except, int32_t line, string func) {
       auto level = LogLevel::Info;
       logMessage(level, formatLogMessage(msg, level, func, line, except));
   }

   void ConsoleLogger::ok(string msg, exception* except, int32_t line, string func) {
       auto level = LogLevel::Ok;
       logMessage(level, formatLogMessage(msg, level, func, line, except));
   }

   void ConsoleLogger::trace(string msg, exception* except, int32_t line, string func) {
       auto level = LogLevel::Trace;
       logMessage(level, formatLogMessage(msg, level, func, line, except));
   }

   void ConsoleLogger::warning(string msg, exception* except, int32_t line, string func) {
       auto level = LogLevel::Warning;
       logMessage(level, formatLogMessage(msg, level, func, line, except));
   }

}
