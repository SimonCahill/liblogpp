/**
 * ILogger.hpp
 *
 * Intuitive logging library for C++ written by Simon Cahill.
 */

#ifndef LIBLOGPP_ILOGGER_HPP
#define LIBLOGPP_ILOGGER_HPP

/****************************
 *	    Local Includes	    *
 ****************************/
#include "LogExtensions.hpp"
#include "LogLevel.hpp"

/***************************
 *	    System Includes    *
 ***************************/

#include <exception>
#include <mutex>
#include <sstream>
#include <string>

#include <fmt/core.h>

namespace logpp {

    using std::exception;
    using std::mutex;
	using std::string;
    using std::stringstream;

    /**
     * @brief Base abstract logger class.
     *
     * This class contains the very most basic implementation of a logger provided by this library.
     * This logger cannot be used directly, or instantiated.
     * Rather, this logger implementation is used as a template for other loggers provided.
     *
     * This class may be inherited by other applications as the developer(s) see fit.
     */
	class ILogger {
   	    public: // +++ STATIC +++
            //==========================================================================================
            // The following block defines all "variables" usable in log++.
            // By putting the different format vars in the format string, the look of the log message
            // may be manipulated.
            // Why this isn't stricly necessary for a logging library, it's definitely nice to have
            // and can give your logging messages a distinctive look.
            // This is especially handy if you're logging to one large file where different programs'
            // log messages are saved.
            //==========================================================================================
            static const string LOG_FMT_DATE; ///! ${date} => the current date w/ the set date format
            static const string LOG_FMT_TIME; ///! ${time} => the current time w/ the set time format
            static const string LOG_FMT_DATETIME; ///! ${datetime} => the current time and date w/ the set formats
            static const string LOG_FMT_LOGLVL; ///! ${llevel} => the log level of the current message
            static const string LOG_FMT_MSG; ///! ${lmsg} => the actual log message
            static const string LOG_FMT_FUNC; ///! ${func} => if the current function was set via param, output that
            static const string LOG_FMT_LINE; ///! ${lineno} => if the current line number was set via param, output that
            static const string LOG_FMT_CLASS; ///! ${class} => if the class name was set, output that
            static const string LOG_FMT_EXCEPT; ///! ${except} => if an exception was passed, output that
            static const string LOG_FMT_APPNAME; ///! ${appname} => if the application's name was set, output that
            static const string LOG_FMT_CUSTOM; ///! ${custom} => this allows for some custom flare to be added to log outputs

	    public:
            virtual ~ILogger(); ///!< Virtual destructor

            /**
             * @brief Gets a value indicating whether to flush the underlying buffer after each write.
             *
             * @return true If the buffer should be flushed after each write.
             * @return false Otherwise.
             */
            bool flushBufferAfterWrite() const { return this->_flushBufferAfterWrite; }

            /**
             * @brief Gets the current max log level for this instance.
             */
            LogLevel getCurrentMaxLogLevel() const { return this->_maxLoggingLevel; }

            /**
             * @brief Gets the name of the application that was set in this logger instance.
             */
            string getCurrentApplicationName() const { return this->_appName; }

            /**
             * @brief Gets the name of the class using this logger. Only handy if multiple loggers are used.
             */
            string getCurrentClassName() const { return this->_className; }

            /**
             * @brief Gets the custom flare set to use when logging.
             */
            string getCurrentCustomFlare() const { return this->_customFlare; }

            /**
             * @brief Gets the string used to format log outputs.
             */
            string getCurrentLoggerFormat() const { return this->_loggerFormat; }

            /**
             * @brief Gets the name of this logger.
             */
            string getCurrentLoggerName() const { return this->_logName; }

            /**
             * @brief Gets the current date as per format rules.
             *
             * @return The current date as defined by _dateFormatString
             */
            virtual string getCurrentDate() const;

            /**
             * @brief Gets the current date as per format rules.
             *
             * @return The current date as defined by _dateTimeFormatString
             */
            virtual string getCurrentDateTime() const;

            /**
             * @brief Gets the newline char required for the operating system currently in use.
             */
            virtual string getOsNewLineChar() const;

            /**
             * @brief Gets the size of the string (in bytes) of the underlying buffer.
             *
             * @return The size (in bytes) of the underlying buffer.
             */
            uint32_t getBufferSize() const { return this->_logBuffer.str().size(); }

            /**
             * @brief Gets the maximum size for the logger buffer.
             *
             * @remarks A size of zero implies the buffer will be flushed after each write and will override @link flushBufferAfterEachWrite @endlink
             *
             * @return The maximum configured buffer size.
             */
            uint32_t getMaxBufferSize() const { return this->_maxBufferSize; }

            /**
             * @brief Gets the current date as per format rules.
             *
             * @return The current date as defined by _timeFormatString
             */
            virtual string getCurrentTime() const;

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
            virtual string formatLogMessage(const string& msg, const LogLevel lvl, const string& func = "", const int32_t line = -1, const exception* except = nullptr);

            /**
             * @brief Flushes the internal buffer; abstract.
             */
            virtual void flushBuffer() = 0;

            /**
             * @brief VIRTUAL - Logs a message.
             */
            virtual void logMessage(const LogLevel level, const string& msg);

            //////////////////////////////
            //      Log Shortcuts       //
            //////////////////////////////
            virtual void debug(const string& msg, const exception* except = nullptr, const int32_t line = -1, const string& func = ""); ///!< A shortcut method for logging debug messages. Abstract.
            virtual void error(const string& msg, const exception* except = nullptr, const int32_t line = -1, const string& func = ""); ///!< A shortcut method for logging error messages. Abstract.
            virtual void fatal(const string& msg, const exception* except = nullptr, const int32_t line = -1, const string& func = ""); ///!< A shortcut method for logging fatal messages. Abstract.
            virtual void info(const string& msg, const exception* except = nullptr, const int32_t line = -1, const string& func = ""); ///!< A shortcut method for logging info messages. Abstract.
            virtual void ok(const string& msg, const exception* except = nullptr, const int32_t line = -1, const string& func = ""); ///!< A shortcut method for logging ok messages. Abstract.
            virtual void trace(const string& msg, const exception* except = nullptr, const int32_t line = -1, const string& func = ""); ///!< A shortcut method for logging trace messages. Abstract.
            virtual void warning(const string& msg, const exception* except = nullptr, const int32_t line = -1, const string& func = ""); ///!< A shortcut method for logging warning messages. Abstract.
            
        #if defined(logpp_USE_PRINTF)
            template<typename... Args>
            void debugFmt(const string& fmt, Args... args) { debug(formatString(fmt, args...)); }

            template<typename... Args>
            void errorFmt(const string& fmt, Args... args) { error(formatString(fmt, args...)); }

            template<typename... Args>
            void fatalFmt(const string& fmt, Args... args) { fatal(formatString(fmt, args...)); }

            template<typename... Args>
            void infoFmt(const string& fmt, Args... args) { info(formatString(fmt, args...)); }

            template<typename... Args>
            void okFmt(const string& fmt, Args... args) { ok(formatString(fmt, args...)); }

            template<typename... Args>
            void traceFmt(const string& fmt, Args... args) { trace(formatString(fmt, args...)); }

            template<typename... Args>
            void warningFmt(const string& fmt, Args... args) { warning(formatString(fmt, args...)); }
        #else
            template<typename... Args>
            void debugFmt(const string& fmt, Args... args) { debug(fmt::format(fmt, args...)); }

            template<typename... Args>
            void errorFmt(const string& fmt, Args... args) { error(fmt::format(fmt, args...)); }

            template<typename... Args>
            void fatalFmt(const string& fmt, Args... args) { fatal(fmt::format(fmt, args...)); }

            template<typename... Args>
            void infoFmt(const string& fmt, Args... args) { info(fmt::format(fmt, args...)); }

            template<typename... Args>
            void okFmt(const string& fmt, Args... args) { ok(fmt::format(fmt, args...)); }

            template<typename... Args>
            void traceFmt(const string& fmt, Args... args) { trace(fmt::format(fmt, args...)); }

            template<typename... Args>
            void warningFmt(const string& fmt, Args... args) { warning(fmt::format(fmt, args...)); }
        #endif // logpp_USE_PRINTF


            /**
             * @brief Sets the application name for this logger instance.
             */
            void setCurrentApplicationName(const string& appName) { this->_appName = appName; }

            /**
             * @brief Sets the name of the class using this instance.
             */
            void setCurrentClassName(const string& _className) { this->_className = _className; }

            /**
             * @brief Sets the custom flare to use with this instance.
             */
            void setCurrentCustomFlare(const string& _customFlare) { this->_customFlare = _customFlare; }

            /**
             * @brief Sets the custom logger format. Default is default
             */
            void setCurrentLoggerFormat(const string& loggerFormat = "[ ${date} ${time} ] [ ${llevel} ] ${lmsg}") { this->_loggerFormat = loggerFormat; }

            /**
             * @brief Sets the custom name for this logger. If default, generates random ID.
             */
            void setCurrentLoggerName(const string& logName = "") { this->_logName = logName; }

            /**
             * @brief Sets the current maximum log level.
             */
            void setCurrentMaxLogLevel(const LogLevel level = LogLevel::Error) { this->_maxLoggingLevel = level; }

            /**
             * @brief Sets a value indicating whether to flush the underlying buffer after each write.
             *
             * @remarks This may be overruled by setting the maximum buffer size to zero!
             *
             * @param flushAfterWrite A value indicating whether to flush the buffer after each write.
             */
            void setFlushAfterWrite(bool flushAfterWrite) { this->_flushBufferAfterWrite = flushAfterWrite; }

            /**
             * @brief Sets the maximum size (in bytes) of the underlying buffer.
             *
             * @remarks Setting this to 0 implies @link flushBufferAfterWrite @endlink.
             *
             * @param maxSize The maximum buffer size in bytes.
             */
            void setMaxBufferSize(const uint32_t maxSize) { this->_maxBufferSize = maxSize; }

	    protected:
	        ILogger(const string& logName, LogLevel maxLevel, uint32_t bufferSize, bool flushBufferAfterWrite); ///!< Base constructor.

            /**
             * @brief Gets a reference to the string stream used as a buffer.
             *
             * @return A reference to the back-end string stream used as a buffer.
             */
            stringstream& getLogBuffer() { return this->_logBuffer; }

			/**
			 * @brief Gets the string representation of the underlying buffer.
			 *
			 * @return The string from the underlying buffer.
			 */
			string getLogBufferAsString() { return getLogBuffer().str(); }

            /**
             * @brief Get the Write Mutex object
             * 
             * @return mutex& A reference to the mutex object.
             */
            mutex& getWriteMutex() { return *_writeMutex; }

	    private:
            static mutex* _writeMutex; ///!< Lock me before writing!

            string          _appName;
            string          _className;
            string          _customFlare;
            string          _loggerFormat;
			string          _logName;

			LogLevel        _maxLoggingLevel;

            string          _dateFormatString;
            string          _dateTimeFormatString;
            string          _timeFormatString;

            // Logger buffer
            bool            _flushBufferAfterWrite;
            stringstream    _logBuffer;
            uint32_t        _maxBufferSize;
    };

}

#endif // LIBLOGPP_ILOGGER_HPP
