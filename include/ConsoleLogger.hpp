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

            virtual void debug(string msg, exception* except = nullptr, int32_t line = -1, string func = "");
            virtual void error(string msg, exception* except = nullptr, int32_t line = -1, string func = "");
            virtual void fatal(string msg, exception* except = nullptr, int32_t line = -1, string func = "");
            virtual void info(string msg, exception* except = nullptr, int32_t line = -1, string func = "");
            virtual void ok(string msg, exception* except = nullptr, int32_t line = -1, string func = "");
            virtual void trace(string msg, exception* except = nullptr, int32_t line = -1, string func = "");
            virtual void warning(string msg, exception* except = nullptr, int32_t line = -1, string func = "");

            void setOutputBadLogsToStderr(bool outputToStderr) { this->_outputBadLogsToStderr = outputToStderr; }
            void setOutputDebugLogsToStderr(bool outputToStderr) { this->_outputDebugToStderr = outputToStderr; }

        private:
            bool _outputBadLogsToStderr;
            bool _outputDebugToStderr;
    };

}

#endif