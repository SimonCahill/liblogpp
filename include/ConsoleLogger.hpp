/**
 * ConsoleLogger.hpp
 *
 * log++ - Intuitive logging library for C++ written by Simon Cahill.
 */

#ifndef LOGPP_CONSOLELOGGER_HPP
#define LOGPP_CONSOLELOGGER_HPP

#include "ILogger.hpp"

namespace logpp {

    class ConsoleLogger: public ILogger {
        public:
            ConsoleLogger(string logName, LogLevel maxLogLevel, bool outputBadLogsToStderr, uint32_t bufferSize, bool flushBufferAfterWrite); ///!< Object constructor.
            virtual ~ConsoleLogger(); ///!< Virtual destructor.
            
            bool outputBadLogsToStderr() { return this->_outputBadLogsToStderr; }
            bool outputDebugLogsToStderr() { return this->_outputDebugToStderr; }

            virtual void flushBuffer();
            virtual void logMessage(LogLevel level, string msg);

            void setOutputBadLogsToStderr(bool outputToStderr) { this->_outputBadLogsToStderr = outputToStderr; }
            void setOutputDebugLogsToStderr(bool outputToStderr) { this->_outputDebugToStderr = outputToStderr; }

        private:
            bool _outputBadLogsToStderr;
            bool _outputDebugToStderr;
    };

}

#endif