/**
 * log.hpp
 *
 * Intuitive logging library for C++ written by Simon Cahill.
 */

 #ifndef LIB_LOGPP_HPP
 #define LIB_LOGPP_HPP

#include <extensions>
#include <iostream>

#include <ILogger.hpp>

 namespace logpp {

     using std::ostream;

     class LogFactory {

         public: // +++ STATIC +++
            buildFileLogger(LogLevel maxLogLevel, string filename, uint32_t bufferSize, bool flushBufferAfterWrite) {
                throw invalid_argument("Method is not implemented.");
            }

            buildConsoleLogger(LogLevel maxLogLevel, bool outputBadLogsToStderr, uint32_t bufferSize, bool flushBufferAfterWrite) {
                throw invalid_argument("Method is not implemented.");
            }

            buildStreamLogger(LogLevel maxLogLevel, ostream outStream, uint32_t bufferSize, bool flushBufferAfterWrite) {
                throw invalid_argument("Method is not implemented.");
            }
     };

 }

 #endif // LIB_LOGPP_HPP