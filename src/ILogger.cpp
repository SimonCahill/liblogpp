/**
 * ILogLevel.cpp
 *
 * log++
 * An intuitive C++ logging library.
 *
 * (c) 2019 Simon Cahill and contributors.
 */

//////////////////////////////////
//	System Includes		//
//////////////////////////////////

//////////////////////////////////
//	Local Includes		//
//////////////////////////////////
#include "ILogger.hpp"

/**
 * The library's main namespace.
 */
namespace logpp {

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
    string ILogger::LOG_FMT_DATE = 	    "${date}"; 	// ${date} => the current date w/ the set date format
    string ILogger::LOG_FMT_TIME = 	    "${time}"; 	// ${time} => the current time w/ the set time format
    string ILogger::LOG_FMT_DATETIME = 	"${datetime}"; 	// ${datetime} => the current time and date w/ the set formats
    string ILogger::LOG_FMT_LOGLVL = 	"${llevel}"; 	// ${llevel} => the log level of the current message
    string ILogger::LOG_FMT_MSG = 	    "${lmsg}"; 	// ${lmsg} => the actual log message
    string ILogger::LOG_FMT_FUNC = 	    "${func}"; 	// ${func} => if the current function was set via param, output that
    string ILogger::LOG_FMT_LINE = 	    "${lineno}"; 	// ${lineno} => if the current line number was set via param, output that
    string ILogger::LOG_FMT_CLASS = 	"${class}"; 	// ${class} => if the class name was set, output that
    string ILogger::LOG_FMT_EXCEPT = 	"${except}"; 	// ${except} => if an exception was passed, output that
    string ILogger::LOG_FMT_APPNAME = 	"${appname}"; 	// ${appname} => if the application's name was set, output that
    string ILogger::LOG_FMT_CUSTOM = 	"${custom}"; 	// ${custom} => this allows for some custom flare to be added to log outputs

    // PROTECTED IMPLEMENTATION

    /**
     * @brief "Default" constructor.
     * Contains the minimum amount of information required to get a logger going.
     *
     * @param logName The name for this logger.
     * @param maxLevel The maximum log level allowed for this instance.
     */
    ILogger::ILogger(loggerName logName, LogLevel maxLevel) {
        this->_logName = logName;
        this->_maxLogLevel = maxLevel;
    }

    /**
     * @brief Virtual method for formatting log messages as desired.
     *
     * This method provides a simple way of creating a custom flare for your log messages.
     * This method may be overridden by classes inheriting this abstract class.
     *
     * @param msg A reference to the message to be logged. This string will be modified!
     */
    void ILogger::formatLogMessage(logMessage& msg) {
        // logFormat local class variable containing formatting
        if (logFormat.empty() || msg.empty()) return;

        string formattedMsg;

        stringReplaceAll(msg, LOG_FMT_DATE, getCurrentDate());
        stringReplaceAll(msg, LOG_FMT_TIME, getCurrentTime());
    }

}
