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
            ConsoleLogger(const string& logName, const LogLevel maxLogLevel, const bool outputBadLogsToStderr, 
                          const uint32_t bufferSize, const bool flushBufferAfterWrite); ///!< Object constructor.
            ConsoleLogger(const string& logName, const LogLevel maxLogLevel, const bool outputBadLogsToStderr,
                          const uint32_t bufferSize, const bool flushBufferAfterWrite, const bool logToFile, const string& logPath,
                          const uint32_t maxFileSize); ///!< Object constructor.
            virtual ~ConsoleLogger(); ///!< Virtual destructor.
            
            /**
             * @brief Gets a value indicating whether to output bad logs to std err or not.
             * 
             * @return true If bad logs should be output to std err.
             * @return false Otherwise.
             */
            bool outputBadLogsToStderr() const { return this->_outputBadLogsToStderr; }

            /**
             * @brief Gets a value indicating whether to output debug logs to std err or not.
             * 
             * @return true If debug logs should be output to std err.
             * @return false Otherwise.
             */
            bool outputDebugLogsToStderr() const { return this->_outputDebugToStderr; }

            virtual void flushBuffer() override; ///!< Flushes the underlying buffer.
            virtual void logMessage(const LogLevel level, const string& msg) override; ///!< Logs a message to the console.
            
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

            /**
             * @brief Gets a pointer to the internal FileLogger object.
             * 
             * @return FileLogger* A pointer to the file logger.
             */
            FileLogger* getInternalFileLogger() const { return this->_fileLogger; }

        protected:
            /**
             * @brief Formats an entire log message which may then be directly printed to any given (string) output.
             *
             * @param msg A reference to a string containing the log message. Also used as the output for the entire (formatted) message.
             * @param lvl The log level for the given message. Used for formatting.
             * @param func The function which called the logger. Used for formatting.
             * @param line The line at which the logger was called. Used for formatting.
             * @param except A pointer to an exception which should be logged.
             *
             * @return Returns the entire formatted message so it may be used in a function call.
             */
            virtual string formatLogMessage(const string& msg, LogLevel lvl, const string& func = "", const int32_t line = -1, const exception* except = nullptr) override;

        private:
            bool _colourLogLevels;
            bool _outputBadLogsToStderr;
            bool _outputDebugToStderr;
            bool _logToFile;

            FileLogger* _fileLogger;
    };

}

#endif