/**
 * ConsoleLogger.hpp
 *
 * log++ - Intuitive logging library for C++ written by Simon Cahill.
 */

/****************************
 *	    Local Includes	    *
 ****************************/
#include "ConsoleLogger.hpp"
#include "LogExtensions.hpp"

/***************************
 *	    System Includes    *
 ***************************/
#include <iostream>
#include <ostream>

namespace logpp {

    using std::iostream;
    using std::ostream;

    /**
     * @brief Construct a new Console Logger:: Console Logger object
     * 
     * @param logName The name for this logger.
     * @param maxLogLevel The maximum logging level to log.
     * @param outputBadLogsToStderr Indicates whether to output bad logs to std error or not.
     * @param bufferSize The maximum buffer size before flushing.
     * @param flushBufferAfterWrite Indicates whether to flush the buffer after each write to it.
     */
    ConsoleLogger::ConsoleLogger(string logName, LogLevel maxLogLevel, bool outputBadLogsToStderr, uint32_t bufferSize, bool flushBufferAfterWrite):
    ILogger(logName, maxLogLevel, flushBufferAfterWrite, bufferSize), _fileLogger(nullptr), _logToFile(false), _colourLogLevels(true) {
        setOutputBadLogsToStderr(outputBadLogsToStderr);
    }

    /**
     * @brief Construct a new Console Logger:: Console Logger object
     * 
     * @param logName The name for this logger.
     * @param maxLogLevel The maximum logging level to log.
     * @param outputBadLogsToStderr Indicates whether to output bad logs to std error or not.
     * @param bufferSize The maximum buffer size before flushing.
     * @param flushBufferAfterWrite Indicates whether to flush the buffer after each write to it.
     * @param logToFile Indicates whether to also log to a file or not.
     * @param logPath The directory in which to create the log file(s).
     * @param maxFileSize The maximum log file size in MiB.
     */
    ConsoleLogger::ConsoleLogger(string logName, LogLevel maxLogLevel, bool outputBadLogsToStderr, uint32_t bufferSize, bool flushBufferAfterWrite,
                                 bool logToFile, string logPath, uint32_t maxFileSize): 
    ConsoleLogger(logName, maxLogLevel, outputBadLogsToStderr, flushBufferAfterWrite, bufferSize) {
        this->_logToFile = logToFile;
        if (_logToFile) {
            _fileLogger = new FileLogger(logName, maxLogLevel, formatString("%s/%s.log", logPath.c_str(), logName.c_str()), bufferSize, maxFileSize, flushBufferAfterWrite, true);
        }
    }

    /**
     * @brief Destroy the Console Logger:: Console Logger object
     */
    ConsoleLogger::~ConsoleLogger() {
        // Destroy FileLogger object if it was set.
        if (_logToFile && _fileLogger != nullptr) {
            delete _fileLogger;
        }
    }

    /**
     * @brief Flushes the underlying buffer to its respective output.
     */
    void ConsoleLogger::flushBuffer() {
        using std::cout;
        using std::endl;

        getWriteMutex().lock();
        // TODO: Implement functionality where bad logs are output to cerr if desired.
        // This will require overriding logMessage()
        auto output = getLogBufferAsString();

        if (output.empty()) return;
        
        if (*(output.end() - 1) == getOsNewLineChar()) {
            cout << output;
        } else cout << output << endl;
        
        clearStringStream(getLogBuffer());
        getWriteMutex().unlock();
    }

    /**
     * @brief Overridden method; logs messages to the internal buffer or standard error output.
     * 
     * @remarks This method is overridden. While the core functionality remains the same, 
     * the major difference is that "bad" logs are automatically redirected to stderr, instead of 
     * being buffered.
     * A "bad" log is any log level >= 4.
     * 
     * @param level The log level of the message.
     * @param msg The message to be output.
     */
    void ConsoleLogger::logMessage(LogLevel level, string msg) {
        using std::cerr;
        using std::endl;

        if (level > getCurrentMaxLogLevel()) return;

        if (_logToFile && _fileLogger != nullptr)
            _fileLogger->logMessage(level, msg);

        getWriteMutex().lock();
        if (outputBadLogsToStderr() && isBadLog(level)) {
            // Bypass log buffer and print directly to stderr.
            if (*(msg.end() - 1) == getOsNewLineChar()) {
                cerr << msg;
            } else cerr << msg << endl;

            getWriteMutex().unlock();
            return;
        }
        getWriteMutex().unlock();

        ILogger::logMessage(level, msg);
    }

    /**
     * @brief Virtual method for formatting log messages as desired.
     *
     * This method provides a simple way of creating a custom flare for your log messages.
     * This method may be overridden by classes inheriting this abstract class.
     *
     * @param msg A reference to the message to be logged. This string will be modified!
     */
    string ConsoleLogger::formatLogMessage(string& msg, LogLevel lvl, string func, int32_t line, exception* except) {
        // logFormat local class variable containing formatting
        if (getCurrentLoggerFormat().empty() || msg.empty()) {
            return msg;
        }

        string formattedMsg = ILogger::formatLogMessage(msg, lvl, func, line, except);
        if (_colourLogLevels) {
            auto foreground = TextColour::None;
            auto background = TextColour::None;

            switch (lvl) {
                case LogLevel::Debug:
                    foreground = TextColour::CyanForeground;
                    break;
                case LogLevel::Error:
                    foreground = TextColour::RedForeground;
                    break;
                case LogLevel::Fatal:
                    foreground = TextColour::BlackForeground;
                    background = TextColour::RedBackground;
                    break;
                case LogLevel::Info:
                    foreground = TextColour::BlueForeground;
                    break;
                case LogLevel::Ok:
                    foreground = TextColour::GreenForeground;
                    break;
                case LogLevel::Trace:
                    foreground = TextColour::MagentaForeground;
                    break;
                case LogLevel::Warning:
                    foreground = TextColour::YellowForeground;
                    break;
            }
            stringReplace(formattedMsg, toString(lvl), toString(lvl, foreground, background));
        }

        return formattedMsg;
    }

}
