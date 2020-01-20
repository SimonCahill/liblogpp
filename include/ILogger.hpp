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
#include <sstream>
#include <string>

namespace logpp {

    using std::exception;
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
            const static string LOG_FMT_DATE; ///! ${date} => the current date w/ the set date format
            const static string LOG_FMT_TIME; ///! ${time} => the current time w/ the set time format
            const static string LOG_FMT_DATETIME; ///! ${datetime} => the current time and date w/ the set formats
            const static string LOG_FMT_LOGLVL; ///! ${llevel} => the log level of the current message
            const static string LOG_FMT_MSG; ///! ${lmsg} => the actual log message
            const static string LOG_FMT_FUNC; ///! ${func} => if the current function was set via param, output that
            const static string LOG_FMT_LINE; ///! ${lineno} => if the current line number was set via param, output that
            const static string LOG_FMT_CLASS; ///! ${class} => if the class name was set, output that
            const static string LOG_FMT_EXCEPT; ///! ${except} => if an exception was passed, output that
            const static string LOG_FMT_APPNAME; ///! ${appname} => if the application's name was set, output that
            const static string LOG_FMT_CUSTOM; ///! ${custom} => this allows for some custom flare to be added to log outputs

            const static string DEFAULT_LOG_FMT; ///!< logpp's default log format: [ ${date} ${time} ] [ ${llevel} ] ${lmsg}
            const static string EXCEPT_LOG_FMT; ///!< Adds exception logging to a log format: [ ${datetime} ] [ ${llevel} ] ${lmsg}: ${except}  
            const static string VERBOSE_LOG_FMT; ///!< Very verbose logging for debug purposes: [ ${datetime} ] [ ${llevel} ] [ ${func}:${lineno} ] ${lmsg}
            const static string CLASS_LOG_FMT; ///!< A logger format containing the current class: [ ${datetime} ] [ ${llevel} ] [ ${class} ] ${lmsg}
            const static string VERBOSE_CLASS_LOG_FMT; ///!< A verbose class logging format: [ ${datetime} ] [ ${llevel} ] [ ${class}#${func}:${lineno} ] ${lmsg}

	    public:
            virtual ~ILogger(); ///!< Virtual destructor

            /**
             * @brief Gets a value indicating whether to flush the underlying buffer after each write.
             *
             * @return true If the buffer should be flushed after each write.
             * @return false Otherwise.
             */
            bool flushBufferAfterWrite() { return this->_flushBufferAfterWrite; }

            /**
             * @brief Gets the current max log level for this instance.
             */
            LogLevel getCurrentMaxLogLevel() { return this->_maxLoggingLevel; }

            /**
             * @brief Gets the name of the application that was set in this logger instance.
             */
            string getCurrentApplicationName() { return this->_appName; }

            /**
             * @brief Gets the name of the class using this logger. Only handy if multiple loggers are used.
             */
            string getCurrentClassName() { return this->_className; }

            /**
             * @brief Gets the custom flare set to use when logging.
             */
            string getCurrentCustomFlare() { return this->_customFlare; }

            /**
             * @brief Gets the string used to format log outputs.
             */
            string getCurrentLoggerFormat() { return this->_loggerFormat; }

            /**
             * @brief Gets the name of this logger.
             */
            string getCurrentLoggerName() { return this->_logName; }

            /**
             * @brief Gets the current date as per format rules.
             *
             * @return The current date as defined by _dateFormatString
             */
            virtual string getCurrentDate();

            /**
             * @brief Gets the current date as per format rules.
             *
             * @return The current date as defined by _dateTimeFormatString
             */
            virtual string getCurrentDateTime();

            /**
             * @brief Gets the size of the string (in bytes) of the underlying buffer.
             *
             * @return The size (in bytes) of the underlying buffer.
             */
            uint32_t getBufferSize() { return this->_logBuffer.str().size(); }

            /**
             * @brief Gets the maximum size for the logger buffer.
             *
             * @remarks A size of zero implies the buffer will be flushed after each write and will override @link flushBufferAfterEachWrite @endlink
             *
             * @return The maximum configured buffer size.
             */
            uint32_t getMaxBufferSize() { return this->_maxBufferSize; }

            /**
             * @brief Gets the current date as per format rules.
             *
             * @return The current date as defined by _timeFormatString
             */
            virtual string getCurrentTime();

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
            virtual string formatLogMessage(string& msg, LogLevel lvl, string func = "", int32_t line = -1, exception* except = nullptr);

            /**
             * @brief Flushes the internal buffer; abstract.
             */
            virtual void flushBuffer() = 0;

            /**
             * @brief VIRTUAL - Logs a message.
             */
            virtual void logMessage(LogLevel level, string msg);

            //////////////////////////////
            //      Log Shortcuts       //
            //////////////////////////////
            virtual void debug(string msg, exception* except = nullptr, int32_t line = -1, string func = ""); ///!< A shortcut method for logging debug messages. Abstract.
            virtual void error(string msg, exception* except = nullptr, int32_t line = -1, string func = ""); ///!< A shortcut method for logging error messages. Abstract.
            virtual void fatal(string msg, exception* except = nullptr, int32_t line = -1, string func = ""); ///!< A shortcut method for logging fatal messages. Abstract.
            virtual void info(string msg, exception* except = nullptr, int32_t line = -1, string func = ""); ///!< A shortcut method for logging info messages. Abstract.
            virtual void ok(string msg, exception* except = nullptr, int32_t line = -1, string func = ""); ///!< A shortcut method for logging ok messages. Abstract.
            virtual void trace(string msg, exception* except = nullptr, int32_t line = -1, string func = ""); ///!< A shortcut method for logging trace messages. Abstract.
            virtual void warning(string msg, exception* except = nullptr, int32_t line = -1, string func = ""); ///!< A shortcut method for logging warning messages. Abstract.

            /**
             * @brief Sets the application name for this logger instance.
             */
            void setCurrentApplicationName(string appName) { this->_appName = appName; }

            /**
             * @brief Sets the name of the class using this instance.
             */
            void setCurrentClassName(string _className) { this->_className = _className; }

            /**
             * @brief Sets the custom flare to use with this instance.
             */
            void setCurrentCustomFlare(string _customFlare) { this->_customFlare = _customFlare; }

            /**
             * @brief Sets the custom logger format. Default is default
             */
            void setCurrentLoggerFormat(string loggerFormat = DEFAULT_LOG_FMT) { this->_loggerFormat = loggerFormat; }

            /**
             * @brief Sets the custom name for this logger. If default, generates random ID.
             */
            void setCurrentLoggerName(string logName = "") { this->_logName = logName; }

            /**
             * @brief Sets the current maximum log level.
             */
            void setCurrentMaxLogLevel(LogLevel level = LogLevel::Error) { this->_maxLoggingLevel = level; }

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
            void setMaxBufferSize(uint32_t maxSize) { this->_maxBufferSize = maxSize; }

	    protected:
	        ILogger(string logName, LogLevel maxLevel, uint32_t bufferSize, bool flushBufferAfterWrite); ///!< Base constructor.

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

	    private:
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
