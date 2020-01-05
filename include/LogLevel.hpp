/**
 * liblog++.hpp
 *
 * Intuitive logging library for C++ written by Simon Cahill.
 */

#ifndef LIBLOGPP_LOGLEVEL_HPP
#define LIBLOGPP_LOGLEVEL_HPP

/***************************
 *	    Local Includes	   *
 ***************************/

 #include "Extensions.hpp"

/***************************
 *	    System Includes    *
 ***************************/
 #include <cstdlib>
 #include <string>

namespace logpp {

    /**
     * @brief Enumeration containing the different levels of logging achievable.
     * See the individual enumeration values for more information.
     */
    enum class LogLevel {
        /**
         * @brief This is good, this is fine.
         * 
         * A log message notifying that something is good.
         * Lowest level of logging possible.
         */
        Ok = 0,

        /**
         * @brief Informational log. Completely neutral.
         * 
         * Default setting.
         */
        Info = 1,

        /**
         * @brief Something looks suspicious. Maybe keep an eye out on this one.
         */
        Warning = 2,

        /**
         * @brief Something went wrong, but I can still recover. 'Tis not the blow of death.
         */
        Error = 3,

        /**
         * @brief Screw this, I'm going home!
         *
         * This type of log message means an error has occurred from which an application can/should not recover from.
         */
        Fatal = 4,

        /**
         * @brief Should be used for debugging purposes only.
         * 
         * This will spam the crap out of your terminal/log file.
         * You have been warned.
         */
        Debug = 5,

        /**
         * @brief Should be used for development purposes only. 
         * 
         * If you thought debug logs were spammy, wait 'till you see these!
         */
        Trace = 6
    };

    using std::atoi;
    using std::string;

    /**
     * @brief Gets a value indicating whether a given log level is bad or not.
     *
     * @returns @code true @endcode if the log level is considered bad.
     */
    bool isBadLog(LogLevel level) { return ((uint32_t)level) >= 4; }

    /**
     * @brief Attempts to parse a string value to a LogLevel value.
     * 
     * @param level The string to parse.
     * @param out A reference to a LogLevel variable which will contain the parsed value.
     * @return true If parsing was successful and a matching value was found.
     * @return false Otherwise.
     */
    bool tryParseLogLevel(string level, LogLevel& out) {
        stringToLower(level);
        auto cString = level.c_str();
        auto numericValue = strtol(cString, nullptr, 10);

         if (level == "ok" || numericValue == 0) {
             out = LogLevel::Ok;
             return true;
         } else if (level == "info" || numericValue == 1) {
             out = LogLevel::Info;
             return true;
         } else if (level == "warning" || numericValue == 2) {
             out = LogLevel::Warning;
             return true;
         } else if (level == "fatal" || numericValue == 3) {
             out = LogLevel::Fatal;
             return true;
         } else if (level == "debug" || numericValue == 4) {
             out = LogLevel::Debug;
             return true;
         } else if (level == "trace" || numericValue == 5) {
             out = LogLevel::Trace;
             return true;
         }

         return false;
    }

    string toString(const LogLevel level) {
        switch (level) {
            case LogLevel::Ok: return "Ok";
            case LogLevel::Info: return "Info";
            case LogLevel::Warning: return "Warning";
            case LogLevel::Error: return "Error";
            case LogLevel::Fatal: return "Fatal";
            case LogLevel::Debug: return "Debug";
            case LogLevel::Trace: return "Trace";
            default: return "Unknown";
        }
    }

}

#endif // LIBLOGPP_LOGLEVEL_HPP
