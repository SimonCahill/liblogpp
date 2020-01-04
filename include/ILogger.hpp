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
#include "Extensions.hpp"
#include "LogLevel.hpp"

/***************************
 *	    System Includes    *
 ***************************/

#include <exception>
#include <string>

namespace logpp {

    using std::exception;
	using std::string;

    //////////////////////////
    //      TYPEDEFS        //
    //////////////////////////

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
            static string LOG_FMT_DATE; // ${date} => the current date w/ the set date format
            static string LOG_FMT_TIME; // ${time} => the current time w/ the set time format
            static string LOG_FMT_DATETIME; // ${datetime} => the current time and date w/ the set formats
            static string LOG_FMT_LOGLVL; // ${llevel} => the log level of the current message
            static string LOG_FMT_MSG; // ${lmsg} => the actual log message
            static string LOG_FMT_FUNC; // ${func} => if the current function was set via param, output that
            static string LOG_FMT_LINE; // ${lineno} => if the current line number was set via param, output that
            static string LOG_FMT_CLASS; // ${class} => if the class name was set, output that
            static string LOG_FMT_EXCEPT; // ${except} => if an exception was passed, output that
            static string LOG_FMT_APPNAME; // ${appname} => if the application's name was set, output that
            static string LOG_FMT_CUSTOM; // ${custom} => this allows for some custom flare to be added to log outputs

	    public:
            virtual ~ILogger() { /* No cleanup required here for now */ } ///!< Virtual destructor

            LogLevel getCurrentMaxLogLevel(); ///!< Gets the current max log level for this instance.

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
             * @brief Gets the current date as per format rules.
             *
             * @return The current date as defined by _timeFormatString
             */
            virtual string getCurrentTime();

            /**
             * @brief VIRTUAL - Logs a message.
             */
            virtual void logMessage(LogLevel level, string msg) = 0;

            //////////////////////////////
            //      Log Shortcuts       //
            //////////////////////////////
            virtual void debug(string msg, exception* except = nullptr, int32_t line = -1, string func = "") = 0;
            virtual void error(string msg, exception* except = nullptr, int32_t line = -1, string func = "") = 0;
            virtual void fatal(string msg, exception* except = nullptr, int32_t line = -1, string func = "") = 0;
            virtual void info(string msg, exception* except = nullptr, int32_t line = -1, string func = "") = 0;
            virtual void ok(string msg, exception* except = nullptr, int32_t line = -1, string func = "") = 0;
            virtual void trace(string msg, exception* except = nullptr, int32_t line = -1, string func = "") = 0;
            virtual void warning(string msg, exception* except = nullptr, int32_t line = -1, string func = "") = 0;

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
            void setCurrentLoggerFormat(string loggerFormat = "[ ${datetime} ] [ ${llevel} ] ${lmsg}") { this->_loggerFormat = loggerFormat; }

            /**
             * @brief Sets the custom name for this logger. If default, generates random ID.
             */
            void setCurrentLoggerName(string logName = "") { this->_logName = logName; }

            /**
             * @brief Sets the current maximum log level.
             */
            void setCurrentMaxLogLevel(LogLevel level = LogLevel::Error) { this->_maxLoggingLevel = level; }

	    protected:
	        ILogger(string logName, LogLevel maxLevel);

            virtual string formatLogMessage(string& msg, LogLevel lvl, string func = "", int32_t line = -1, exception* except = nullptr);

	    private:
            string   _appName;
            string   _className;
            string   _customFlare;
            string   _loggerFormat;
			string   _logName;

			LogLevel _maxLoggingLevel;

            string   _dateFormatString;
            string   _dateTimeFormatString;
            string   _timeFormatString;
    };

}

#endif // LIBLOGPP_ILOGGER_HPP
