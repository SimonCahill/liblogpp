/**
 * ConsoleLogger.hpp
 *
 * log++ - Intuitive logging library for C++ written by Simon Cahill.
 */

#ifndef LOGPP_CONSOLELOGGER_HPP
#define LOGPP_CONSOLELOGGER_HPP

#include "ILogger.hpp"
#include "FileLogger.hpp"

namespace logpp {

    /**
     * @brief A basic console logger for your logging pleasure.
     * 
     * This object logs messages to the standard outputs.
     * Different configurations may be used to modify the behaviour of the logger, such as outputting bad logs to the standard error.
     */
    class ConsoleLogger: public ILogger {
        public:
            ConsoleLogger(string logName, LogLevel maxLogLevel, bool outputBadLogsToStderr, 
                          uint32_t bufferSize, bool flushBufferAfterWrite); ///!< Object constructor.
            ConsoleLogger(string logName, LogLevel maxLogLevel, bool outputBadLogsToStderr,
                          uint32_t bufferSize, bool flushBufferAfterWrite, bool logToFile, string logPath,
                          uint32_t maxFileSize); ///!< Object constructor.
            virtual ~ConsoleLogger(); ///!< Virtual destructor.
            
            /**
             * @brief Gets a value indicating whether to output bad logs to std err or not.
             * 
             * @return true If bad logs should be output to std err.
             * @return false Otherwise.
             */
            bool outputBadLogsToStderr() { return this->_outputBadLogsToStderr; }

            /**
             * @brief Gets a value indicating whether to output debug logs to std err or not.
             * 
             * @return true If debug logs should be output to std err.
             * @return false Otherwise.
             */
            bool outputDebugLogsToStderr() { return this->_outputDebugToStderr; }

            virtual void flushBuffer(); ///!< Flushes the underlying buffer.
            virtual void logMessage(LogLevel level, string msg); ///!< Logs a message to the console.
            
            /**
             * @brief Sets a value indicating whether to output bad logs to std err.
             * 
             * @param outputToStderr True if bad logs should be output to std err.
             */
            void setOutputBadLogsToStderr(bool outputToStderr) { this->_outputBadLogsToStderr = outputToStderr; }

            /**
             * @brief Sets a value indicating whether to output debug logs to std err or not.
             * 
             * @param outputToStderr True if debug logs should be output to std err or not.
             */
            void setOutputDebugLogsToStderr(bool outputToStderr) { this->_outputDebugToStderr = outputToStderr; }

        private:
            bool _outputBadLogsToStderr;
            bool _outputDebugToStderr;
            bool _logToFile;

            FileLogger* _fileLogger;
    };

}

#endif