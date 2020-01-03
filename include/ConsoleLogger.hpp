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
            ConsoleLogger(string logName, LogLevel maxLogLevel, bool outputBadLogsToStderr, uint32_t bufferSize, bool flushBufferAfterWrite);
            
            bool flushBufferAfterWrite() { return this->_flushBufferAfterWrite; }
            bool outputBadLogsToStderr() { return this->_outputBadLogsToStderr; }
            bool outputDebugLogsToStderr() { return this->_outputDebugToStderr; }

            uint32_t getBufferSize() { return this->_bufferSize; }

            virtual void logMessage(LogLevel level, string msg);

            virtual void debug(string msg, exception* except = nullptr, int32_t line = -1, string func = "");
            virtual void error(string msg, exception* except = nullptr, int32_t line = -1, string func = "");
            virtual void fatal(string msg, exception* except = nullptr, int32_t line = -1, string func = "");
            virtual void info(string msg, exception* except = nullptr, int32_t line = -1, string func = "");
            virtual void ok(string msg, exception* except = nullptr, int32_t line = -1, string func = "");
            virtual void trace(string msg, exception* except = nullptr, int32_t line = -1, string func = "");
            virtual void warning(string msg, exception* except = nullptr, int32_t line = -1, string func = "");

            void setBufferSize(bool bufSize) { this->_bufferSize = bufSize; }
            void setFlushAfterWrite(bool flushAfterWrite) { this->_flushBufferAfterWrite = flushAfterWrite; }
            void setOutputBadLogsToStderr(bool outputToStderr) { this->_outputBadLogsToStderr = outputToStderr; }
            void setOutputDebugLogsToStderr(bool outputToStderr) { this->_outputDebugToStderr = outputToStderr; }

        private:
            bool _flushBufferAfterWrite;
            bool _outputBadLogsToStderr;
            bool _outputDebugToStderr;

            uint32_t _bufferSize;
    };

}

#endif