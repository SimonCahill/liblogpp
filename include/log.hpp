/**
 * log.hpp
 *
 * Intuitive logging library for C++ written by Simon Cahill.
 */

 #ifndef LIB_LOGPP_HPP
 #define LIB_LOGPP_HPP

#include <iostream>

#include <ConsoleLogger.hpp>
#include <LogExtensions.hpp>
// #include <StreamLogger.hpp>

 namespace logpp {

     using std::invalid_argument;
     using std::ostream;

     class LogFactory {
         public: // +++ STATIC +++
            /**
             * @brief Static member; Builds and returns a file logger.
             * 
             * @param maxLogLevel The maximum log level for this logger.
             * @param filename The file name / path to where the log should be written.
             * @param bufferSize The maximum buffer size for the logger.
             * @param flushBufferAfterWrite A value indicating whether to flush the buffer after each write.
             * 
             * @return ILogger* A pointer to an instance of the generated logger. May/Should be swapped over to a managed pointer. 
             */
            static ILogger* buildFileLogger(LogLevel maxLogLevel, string filename, uint32_t bufferSize, bool flushBufferAfterWrite) {
                throw invalid_argument("Method is not implemented.");
                return nullptr;
            }

            /**
             * @brief Static member; Builds and returns a console logger.
             * 
             * @param maxLogLevel The maximum log level for this logger.
             * @param outputBadLogsToStderr A value indicating whether to output bad logs to the standard error.
             * @param bufferSize The maximum buffer size for the logger.
             * @param flushBufferAfterWrite A value indicating whether to flush the buffer after each write.
             * 
             * @return ILogger* A pointer to an instance of the generated logger. May/Should be swapped over to a managed pointer. 
             */
            static ILogger* buildConsoleLogger(LogLevel maxLogLevel, bool outputBadLogsToStderr, uint32_t bufferSize, bool flushBufferAfterWrite) {
                throw invalid_argument("Method is not implemented.");
                return nullptr;
            }

            /**
             * @brief Static member; Builds and returns a stream logger.
             * 
             * @param maxLogLevel The maximum log level for this logger.
             * @param outStream A reference to the stream to output to.
             * @param bufferSize The maximum buffer size for the logger.
             * @param flushBufferAfterWrite A value indicating whether to flush the buffer after each write.
             * 
             * @return ILogger* A pointer to an instance of the generated logger. May/Should be swapped over to a managed pointer. 
             */
            static ILogger* buildStreamLogger(LogLevel maxLogLevel, ostream& outStream, uint32_t bufferSize, bool flushBufferAfterWrite) {
                throw invalid_argument("Method is not implemented.");
                return nullptr;
            }
     };

 }

 #endif // LIB_LOGPP_HPP