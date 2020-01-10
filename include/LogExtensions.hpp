/**
 * LogExtensions.hpp
 *
 * Intuitive logging library for C++ written by Simon Cahill.
 */

#ifndef LIBLOGPP_EXTENSIONS_HPP
#define LIBLOGPP_EXTENSIONS_HPP

/***************************
 *	    System Includes    *
 ***************************/

 #include <algorithm>
 #include <cctype>
 #include <iostream>
 #include <memory>
 #include <string>

namespace logpp {

    using std::iostream;
    using std::string;
    using std::tolower;
    using std::toupper;
    using std::transform;
    using std::unique_ptr;

    /**
     * @brief Returns a value indicating whether a given string contains a certain value.
     *
     * @param haystack A reference to a string variable in which to search for the needle.
     * @param needle The needle to search for in the haystack.
     *
     * @return @code true @endcode if the haystack contains the given needle.
     */
    inline bool stringContains(string& haystack, const string needle) {
        return (haystack.find(needle) != string::npos);
    }

    /**
     * @brief Replaces the first instance of needle with the replacement value in the haystack.
     *
     * @param haystack A reference to a string variable in which to search for the needle.
     * @param needle The needle to search for in the haystack.
     * @param replacement The replacement value for the needle.
     *
     * @return @code true @endcode if the needle was replaced.
     */
    inline bool stringReplace(string& haystack, const string needle, const string replacement) {
        auto firstPosition = haystack.find(needle);

        // Return false if no needle was found
        if (firstPosition == string::npos) return false;

        haystack.replace(firstPosition, needle.length(), replacement);
        return true;
    }

    /**
     * @brief Converts a mixed-case string to a lower-case string.
     *
     * @param mixedCase The string to convert.
     * @return string The converted string.
     */
    inline string stringToLower(string& mixedCase) {
        transform(mixedCase.begin(), mixedCase.end(), mixedCase.begin(), [&](uint8_t _char) { return tolower(_char); });

        return mixedCase;
    }

    /**
     * @brief Converts a mixed-case string to an upper-case string.
     *
     * @param mixedCase The string to convert.
     * @return string The converted string.
     */
    inline string stringToUpper(string& mixedCase) {
        transform(mixedCase.begin(), mixedCase.end(), mixedCase.begin(), [&](uint8_t _char) { return toupper(_char); });

        return mixedCase;
    }


    /**
     * @brief Replaces all instances of needle with replacement in haystack.
     *
     * Checks for all instances of a given needle in a haystack and replaces them with
     * the respective replacement.
     *
     * @param haystack The string in which to replace.
     * @param needle The needle to look for in the haystack.
     * @param replacement The replacement value for needle.
     */
    inline void stringReplaceAll(string& haystack, const string needle, string replacement) {
        if (haystack.empty() || needle.empty() || replacement.empty()) {
            return; // Simply return if either are empty
        }

        while (stringReplace(haystack, needle, replacement)) ;
    }

    /**
     * @brief Formats a std string object.
     * 
     * @tparam Args The formatting argument types.
     * @param format The format string.
     * @param args The format arguments (strings must be converted to C-style strings!)
     * 
     * @return string The formatted string. 
     */
    template<typename... Args>
    string formatString(const string& format, Args... args)  {
        auto stringSize = snprintf(NULL, 0, format.c_str(), args...) + 1; // +1 for \0
        unique_ptr<char[]> buffer(new char[stringSize]);

        snprintf(buffer.get(), stringSize, format.c_str(), args...);

        return string(buffer.get(), buffer.get() + stringSize - 1); // std::string handles termination for us.
    }

    /**
     * @brief Get the Current Local Time object.
     * 
     * @return struct tm A struct containing the current local time.
     */
    inline struct tm getCurrentLocalTime() {
        auto timeNow = time(NULL);
        auto timeStruct = *localtime(&timeNow);

        return timeStruct;
    }

}

#endif // LIBLOGPP_EXTENSIONS_HPP
