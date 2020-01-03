/**
 * ConsoleLogger.hpp
 *
 * log++ - Intuitive logging library for C++ written by Simon Cahill.
 */

 #include "ConsoleLogger.hpp"

 namespace logpp {

     using std::cerr;
     using std::cout;
     using std::endl;

    ConsoleLogger::ConsoleLogger(string logName, Loglevel maxLogLevel, bool outputBadLogsToStderr, uint32_t bufferSize, bool flushBufferAfterWrite):
    ILogger(logName, maxLogLevel) {
        setOutputBadLogsToStderr(outputBadLogsToStderr);
        setBufferSize(bufferSize);
        setFlushBufferAfterWrite(flushBufferAfterWrite);
    }

    void ConsoleLogger::logMessage(LogLevel level, string msg, exception* except = nullptr, lineNo line = -1, funcName function = "") {
        switch (level) {
            case LogLevel::Debug: debug(msg, except, line, function); break;
            case LogLevel::Error: error(msg, except, line, function); break;
            case LogLevel::Fatal: fatal(msg, except, line, function); break;
            case LogLevel::Info: info(msg, except, line, function); break;
            case LogLevel::Ok: ok(msg, except, line, function); break;
            case LogLevel::Trace: trace(msg, except, line, function); break;
            case LogLevel::Warning: warning(msg, except, line, function); break;
            default: throw invalid_argument("Encountered unknown log level.");
        }
    }

    void ConsoleLogger::debug(string msg, exception* except = nullptr, lineNo line = -1, funcName func = "") {
        
    }

    void ConsoleLogger::error(string msg, exception* except = nullptr, lineNo line = -1, funcName func = "") {

    }

    void ConsoleLogger::fatal(string msg, exception* except = nullptr, lineNo line = -1, funcName func = "") {

    }

    void ConsoleLogger::info(string msg, exception* except = nullptr, lineNo line = -1, funcName func = "") {

    }

    void ConsoleLogger::ok(string msg, exception* except = nullptr, lineNo line = -1, funcName func = "") {

    }

    void ConsoleLogger::trace(string msg, exception* except = nullptr, lineNo line = -1, funcName func = "") {

    }

    void ConsoleLogger::warning(string msg, exception* except = nullptr, lineNo line = -1, funcName func = "") {

    }


 };
