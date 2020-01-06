/**
 * @file LogLevel.cpp
 * @author Simon Cahill (simon@h3lix.de)
 * @brief Contains the implementation of certain functions from the LogLevel.hpp.
 * @version 0.1
 * @date 2020-01-06
 * 
 * @copyright Copyright (c) 2020 Simon Cahill and contributors.
 * 
 */

/***************************
 *	    Local Includes	   *
 ***************************/

 #include "LogLevel.hpp"

/***************************
 *	    System Includes    *
 ***************************/

namespace logpp {

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

    /**
     * @brief Converts a log level to its string form.
     * 
     * @param level The log level to convert.
     * 
     * @return string The string representation of the log level.
     */
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
    
} // namespace logpp
