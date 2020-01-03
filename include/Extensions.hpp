/**
 * liblog++.hpp
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
 #include <string>

namespace logpp {

    using std::string;
    using std::tolower;
    using std::toupper;
    using std::transform;

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
        transform(mixedCase.begin(), mixedCase.end(), mixedCase.begin() [&](uint8_t _char) { return tolower(_char); });

        return mixedCase;
    }

    /**
     * @brief Converts a mixed-case string to an upper-case string.
     *
     * @param mixedCase The string to convert.
     * @return string The converted string.
     */
    inline string stringToUpper(string& mixedCase) {
        transform(mixedCase.begin(), mixedCase.end(), mixedCase.begin() [&](uint8_t _char) { return toupper(_char); });

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
        if (haystack.empty() || needle.empty() || replacement.empty()) return; // Simply return if either are empty

        while (stringContains(haystack, needle)) {
            stringReplace(haystack, needle, replacement);
        }
    }

}

#endif // LIBLOGPP_EXTENSIONS_HPP
