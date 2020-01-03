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
            ConsoleLogger(string logName, Loglevel maxLogLevel, bool outputBadLogsToStderr, uint32_t bufferSize, bool flushBufferAfterWrite);
            
            bool flushBufferAfterWrite() { return this->_flushBufferAfterWrite; }
            bool outputBadLogsToStderr() { return this->_outputBadLogsToStderr; }

            uint32_t getBufferSize() { return this->_bufferSize; }

            virtual void logMessage(LogLevel level, logMessage msg, lineNo line = -1, funcName function = "");

            virtual void debug(logMessage msg, exception* except = nullptr, lineNo line = -1, funcName func = "");
            virtual void error(logMessage msg, exception* except = nullptr, lineNo line = -1, funcName func = "");
            virtual void fatal(logMessage msg, exception* except = nullptr, lineNo line = -1, funcName func = "");
            virtual void info(logMessage msg, exception* except = nullptr, lineNo line = -1, funcName func = "");
            virtual void ok(logMessage msg, exception* except = nullptr, lineNo line = -1, funcName func = "");
            virtual void trace(logMessage msg, exception* except = nullptr, lineNo line = -1, funcName func = "");
            virtual void warning(logMessage msg, exception* except = nullptr, lineNo line = -1, funcName func = "");

            void setFlushAfterWrite(bool flushAfterWrite) { this->flushBufferAfterWrite = flushAfterWrite; }
            void setOutputBadLogsToStderr(bool ouputToStderr) { this->outputBadLogsToStderr = outputToStderr; }
            void setBufferSize(bool bufSize) { this->_bufferSize = bufSize; }

        private:
            bool _flushBufferAfterWrite;
            bool _outputBadLogsToStderr;

            uint32_t _bufferSize;
    };

}

#endif