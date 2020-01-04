/**
 * log.hpp
 *
 * Intuitive logging library for C++ written by Simon Cahill.
 */

 #ifndef LIB_LOGPP_HPP
 #define LIB_LOGPP_HPP

#include <iostream>

#include <Extensions.hpp>
#include <ILogger.hpp>
#include <ConsoleLogger.hpp>

 namespace logpp {

     using std::invalid_argument;
     using std::ostream;

     class LogFactory {

         public: // +++ STATIC +++
            ILogger* buildFileLogger(LogLevel maxLogLevel, string filename, uint32_t bufferSize, bool flushBufferAfterWrite) {
                throw invalid_argument("Method is not implemented.");
                return nullptr;
            }

            ILogger* buildConsoleLogger(LogLevel maxLogLevel, bool outputBadLogsToStderr, uint32_t bufferSize, bool flushBufferAfterWrite) {
                throw invalid_argument("Method is not implemented.");
                return nullptr;
            }

            ILogger* buildStreamLogger(LogLevel maxLogLevel, ostream outStream, uint32_t bufferSize, bool flushBufferAfterWrite) {
                throw invalid_argument("Method is not implemented.");
                return nullptr;
            }
     };

 }

 #endif // LIB_LOGPP_HPP