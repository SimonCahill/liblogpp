/**
 * ILogLevel.cpp
 *
 * log++
 * An intuitive C++ logging library.
 *
 * (c) 2019 Simon Cahill and contributors.
 */

//////////////////////////////////
//	    System Includes		    //
//////////////////////////////////
#include <chrono>
#include <ctime>
#include <iostream>

#include <fmt/core.h>
#include <fmt/chrono.h>

//////////////////////////////////
//	    Local Includes		    //
//////////////////////////////////
#include "ILogger.hpp"

/**
 * @brief The library's main namespace.
 */
namespace logpp {

    using std::to_string;

    //===========================
    //		ILogger
    //	    Implementation
    //===========================

    // +++ STATIC +++
    //==========================================================================================
    // The following block defines all "variables" usable in log++.
    // By putting the different format vars in the format string, the look of the log message
    // may be manipulated.
    // Why this isn't stricly necessary for a logging library, it's definitely nice to have
    // and can give your logging messages a distinctive look.
    // This is especially handy if you're logging to one large file where different programs'
    // log messages are saved.
    //==========================================================================================
    const string ILogger::LOG_FMT_DATE  	=   "${date}"; 	    // ${date} => the current date w/ the set date format
    const string ILogger::LOG_FMT_TIME  	=   "${time}"; 	    // ${time} => the current time w/ the set time format
    const string ILogger::LOG_FMT_DATETIME  =   "${datetime}"; 	// ${datetime} => the current time and date w/ the set formats
    const string ILogger::LOG_FMT_LOGLVL  	=   "${llevel}"; 	// ${llevel} => the log level of the current message
    const string ILogger::LOG_FMT_MSG  	    =   "${lmsg}"; 	    // ${lmsg} => the actual log message
    const string ILogger::LOG_FMT_FUNC  	=   "${func}"; 	    // ${func} => if the current function was set via param, output that
    const string ILogger::LOG_FMT_LINE  	=   "${lineno}"; 	// ${lineno} => if the current line number was set via param, output that
    const string ILogger::LOG_FMT_CLASS  	=   "${class}"; 	// ${class} => if the class name was set, output that
    const string ILogger::LOG_FMT_EXCEPT  	=   "${except}"; 	// ${except} => if an exception was passed, output that
    const string ILogger::LOG_FMT_APPNAME   =   "${appname}"; 	// ${appname} => if the application's name was set, output that
    const string ILogger::LOG_FMT_CUSTOM  	=   "${custom}"; 	// ${custom} => this allows for some custom flare to be added to log outputs

    mutex* ILogger::_writeMutex = new mutex();

    // PROTECTED IMPLEMENTATION

    /**
     * @brief "Default" constructor.
     * Contains the minimum amount of information required to get a logger going.
     *
     * @param logName The name for this logger.
     * @param maxLevel The maximum log level allowed for this instance.
     * @param bufferSize The maximum size of the underlying buffer.
     * @param flushBufferAfterWrite A value indicating whether to flush the buffer after each write.
     */
    ILogger::ILogger(const string& logName, LogLevel maxLevel, uint32_t bufferSize, bool flushBufferAfterWrite) {
        this->_logName = logName;
        this->_maxLoggingLevel = maxLevel;
        this->_dateFormatString = "%Y.%m.%d";
        this->_timeFormatString = "%H:%M:%S";
        #ifdef logpp_USE_PRINTF
        this->_dateTimeFormatString = formatString("%s %s", _dateFormatString.c_str(), _timeFormatString.c_str());
        #else
        this->_dateTimeFormatString = fmt::format("{} {}", _dateFormatString, _timeFormatString);
        #endif // logpp_USE_PRINTF

        // Buffer init
        this->_flushBufferAfterWrite = flushBufferAfterWrite;
        this->_maxBufferSize = bufferSize;

        // Set default logger format
        setCurrentLoggerFormat();
    }

    /**
     * @brief Destroy the ILogger::ILogger object.
     * 
     * @remarks Also flushes the buffer.
     */
    ILogger::~ILogger() { }

    /**
     * @brief Virtual method for formatting log messages as desired.
     *
     * This method provides a simple way of creating a custom flare for your log messages.
     * This method may be overridden by classes inheriting this abstract class.
     *
     * @param msg A reference to the message to be logged. This string will be modified!
     */
    string ILogger::formatLogMessage(const string& msg, LogLevel lvl, const string& func, const int32_t line, const exception* except) {
        // logFormat local class variable containing formatting
        if (_loggerFormat.empty() || msg.empty()) {
            return msg;
        }

        string formattedMsg = getCurrentLoggerFormat();

        // FIX: For some reason, this only works when passing the strings as a C string?!
        stringReplaceAll(formattedMsg, LOG_FMT_DATE, getCurrentDate());
        stringReplaceAll(formattedMsg, LOG_FMT_TIME, getCurrentTime());
        stringReplaceAll(formattedMsg, LOG_FMT_DATETIME, getCurrentDateTime());
        stringReplaceAll(formattedMsg, LOG_FMT_LOGLVL, toString(lvl));
        stringReplaceAll(formattedMsg, LOG_FMT_MSG, msg);

        if (!_className.empty()) {
            stringReplaceAll(formattedMsg, LOG_FMT_CLASS, _className);
        } if (!_appName.empty()) {
            stringReplaceAll(formattedMsg, LOG_FMT_APPNAME, _appName);
        } if (!_customFlare.empty()) {
            stringReplaceAll(formattedMsg, LOG_FMT_CUSTOM, _customFlare);
        } if (!func.empty()) {
            stringReplaceAll(formattedMsg, LOG_FMT_FUNC, func);
        } if (line >= 0) {
            stringReplaceAll(formattedMsg, LOG_FMT_LINE, to_string(line));
        } if (except != nullptr) {
            stringReplaceAll(formattedMsg, LOG_FMT_EXCEPT, except->what());
        }

        return formattedMsg;
    }

    // PUBLIC IMPLEMENTATION

    /**
     * @brief Gets the current date as per format rules.
     *
     * @return The current date as defined by _dateFormatString
     */
    string ILogger::getCurrentDate() const {
        auto timeStruct = getCurrentLocalTime();

        #ifdef logpp_USE_PRINTF
        string charBuffer;
        strftime(&charBuffer[0], 128, _dateFormatString.c_str(), &timeStruct);
        return charBuffer;
        #else
        return fmt::format("{:" + _dateFormatString + "}", timeStruct);
        #endif // logpp_USE_PRINTF
    }

    /**
     * @brief Gets the current date as per format rules.
     *
     * @return The current date as defined by _dateTimeFormatString
     */
    string ILogger::getCurrentDateTime() const {
        tm timeStruct = getCurrentLocalTime();
        
        #ifdef logpp_USE_PRINTF
        char charBuffer[128];
        strftime(&charBuffer[0], 128, _dateTimeFormatString.c_str(), &timeStruct);
        return charBuffer;
        #else
        return fmt::format("{:" + _dateTimeFormatString + "}", timeStruct);
        #endif // logpp_USE_PRINTF

    }

    /**
     * @brief Gets the current date as per format rules.
     *
     * @return The current date as defined by _timeFormatString
     */
    string ILogger::getCurrentTime() const {
        auto timeStruct = getCurrentLocalTime();

        #ifdef logpp_USE_PRINTF
        string charBuffer;
        strftime(&charBuffer[0], 128, _timeFormatString.c_str(), &timeStruct);
        return charBuffer;
        #else
        return fmt::format("{:" + _timeFormatString + "}", timeStruct);
        #endif // logpp_USE_PRINTF
    }

    string ILogger::getOsNewLineChar() const {
        static string newLine = "";

        if (newLine.empty()) {
            std::ostringstream str;
            str << std::endl;
            newLine = str.str();
        }

        return newLine;
    }

    /**
     * @brief Writes a message to the underlying log buffer and flushes the buffer accordingly.
     *
     * @remarks Bad log levels (log levels above four) will cause the buffer to always be flushed in this default implementation!
     *
     * @param level The level of the current log.
     * @param msg The (formatted) message to output.
     */
    void ILogger::logMessage(LogLevel level, const string& msg) {
        // Check if we're supposed to log anything or not
        if (level > this->_maxLoggingLevel) return;

        getWriteMutex().lock();
      
        if (msg.empty()) return;
        else if (level >= _maxLoggingLevel) return;

        using std::endl;
        // _logBuffer << msg << endl; // Add message to buffer
        if (*msg.end() == '\n') {
            _logBuffer << msg;
        } else _logBuffer << msg << endl;

        getWriteMutex().unlock();
        // Now check if we need to flush
        if (isBadLog(level) || (getMaxBufferSize() == 0 || getBufferSize() >= getMaxBufferSize()) || flushBufferAfterWrite()) {
            flushBuffer();
        }
    }

    /**
     * @brief Shortcut method for logging a debug message.
     * 
     * @param msg The pure message.
     * @param except (Optional) The exception thrown.
     * @param line (Optional) The line at which the logger was called.
     * @param func (Optional) The function/method in which the logger was called.
     */
    void ILogger::debug(const string& msg, const exception* except, const int32_t line, const string& func) {
        auto level = LogLevel::Debug;
        logMessage(level, formatLogMessage(msg, level, func, line, except));
    }

    /**
     * @brief Shortcut method for logging an error message.
     * 
     * @param msg The pure message.
     * @param except (Optional) The exception thrown.
     * @param line (Optional) The line at which the logger was called.
     * @param func (Optional) The function/method in which the logger was called.
     */
    void ILogger::error(const string& msg, const exception* except, const int32_t line, const string& func) {
        auto level = LogLevel::Error;
        logMessage(level, formatLogMessage(msg, level, func, line, except));
    }

    /**
     * @brief Shortcut method for logging a fatal message.
     * 
     * @param msg The pure message.
     * @param except (Optional) The exception thrown.
     * @param line (Optional) The line at which the logger was called.
     * @param func (Optional) The function/method in which the logger was called.
     */
    void ILogger::fatal(const string& msg, const exception* except, const int32_t line, const string& func) {
        auto level = LogLevel::Fatal;
        logMessage(level, formatLogMessage(msg, level, func, line, except));
    }

    /**
     * @brief Shortcut method for logging an informational message.
     * 
     * @param msg The pure message.
     * @param except (Optional) The exception thrown.
     * @param line (Optional) The line at which the logger was called.
     * @param func (Optional) The function/method in which the logger was called.
     */
    void ILogger::info(const string& msg, const exception* except, const int32_t line, const string& func) {
        auto level = LogLevel::Info;
        logMessage(level, formatLogMessage(msg, level, func, line, except));
    }

    /**
     * @brief Shortcut method for logging a good message.
     * 
     * @param msg The pure message.
     * @param except (Optional) The exception thrown.
     * @param line (Optional) The line at which the logger was called.
     * @param func (Optional) The function/method in which the logger was called.
     */
    void ILogger::ok(const string& msg, const exception* except, const int32_t line, const string& func) {
        auto level = LogLevel::Ok;
        logMessage(level, formatLogMessage(msg, level, func, line, except));
    }

    /**
     * @brief Shortcut method for logging a trace message.
     * 
     * @param msg The pure message.
     * @param except (Optional) The exception thrown.
     * @param line (Optional) The line at which the logger was called.
     * @param func (Optional) The function/method in which the logger was called.
     */
    void ILogger::trace(const string& msg, const exception* except, const int32_t line, const string& func) {
        auto level = LogLevel::Trace;
        logMessage(level, formatLogMessage(msg, level, func, line, except));
    }

    /**
     * @brief Shortcut method for logging a warning message.
     * 
     * @param msg The pure message.
     * @param except (Optional) The exception thrown.
     * @param line (Optional) The line at which the logger was called.
     * @param func (Optional) The function/method in which the logger was called.
     */
    void ILogger::warning(const string& msg, const exception* except, const int32_t line, const string& func) {
        auto level = LogLevel::Warning;
        logMessage(level, formatLogMessage(msg, level, func, line, except));
    }

}
