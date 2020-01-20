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

 #include "LogExtensions.hpp"
 #include "TextColour.hpp"

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

    const LogLevel LOGLEVEL_MAXVALUE = LogLevel::Trace;
    const LogLevel LOGLEVEL_MINVALUE = LogLevel::Ok;

    using std::atoi;
    using std::string;

    /**
     * @brief Gets a value indicating whether a given log level is bad or not.
     *
     * @returns @code true @endcode if the log level is considered bad.
     */
    inline bool isBadLog(LogLevel level) { return ((uint32_t)level) >= 4; }

    
    bool tryParseLogLevel(string level, LogLevel& out); ///!< Attempts to parse a string to a LogLevel.

    string toString(const LogLevel level); ///!< Converts a log level to its string representation

    string toString(const LogLevel level, TextColour foreground, TextColour Background); ///!< Converts a log level to its string representation and adds colour to it.

    //////////////////////////////////
    //      OPERATOR OVERLOADS      //
    //////////////////////////////////

    /**
     * @brief Operator overload, determines whether one log level is lower than another.
     * 
     * @param a The log level to test.
     * @param b The log level to test against.
     * 
     * @return true If a is less than b. 
     * @return false Otherwise.
     */
    inline bool operator<(LogLevel a, LogLevel b) { return ((int32_t)a) < ((int32_t)b); }

    /**
     * @brief Operator overload, determines whether one log level is less than or equal to another.
     * 
     * @param a The log level to test.
     * @param b The log level to test against.
     * 
     * @return true If a is less than or equal to b. 
     * @return false Otherwise.
     */
    inline bool operator<=(LogLevel a, LogLevel b) { return ((int32_t)a) <= ((int32_t)b); }

    /**
     * @brief Operator overload, determines whether one log level is higher than another.
     * 
     * @param a The log level to test.
     * @param b The log level to test against.
     * 
     * @return true If a is greater than b. 
     * @return false Otherwise.
     */
    inline bool operator>(LogLevel a, LogLevel b) { return ((int32_t)a) > ((int32_t)b); }

    /**
     * @brief Operator overload, determines whether one log level is greater than or equal to another.
     * 
     * @param a The log level to test.
     * @param b The log level to test against.
     * 
     * @return true If a is greater than or equal to b. 
     * @return false Otherwise.
     */
    inline bool operator>=(LogLevel a, LogLevel b) { return ((int32_t)a) >= ((int32_t)b); }

}

#endif // LIBLOGPP_LOGLEVEL_HPP
